/**
 * File: freelist.c
 * Author: Hunter Barclay
 * 
 * This file includes the implementation of the buddy allocator's freelist.
 * Ngl this is like 90% of the allocator, just more strict on the parameters
 * and has minimal error handling.
 * 
 * For the degreelists, I had to do a bit of a funky adding because using
 * the square brackets also derefs it and it really needed to not be doing that.
 * I made it a double pointer but it was dereffing both of the pointers for some
 * reason? Idk.
 */

#include "freelist.h"

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "error.h"
#include "bbm.h"

/**
 * Implementation Types
 */

/**
 * Freeblock, single-linked list node.
 */
typedef struct t_FreeBlock {
  struct t_FreeBlock *next;
} *FreeBlock;

/**
 * Heap of linked list free blocks for degree,
 * as well as an allocated bitmap.
 */
typedef struct t_DegreeList {
  BBM map;
  FreeBlock head;
} *DegreeList;

/**
 * FreeList internal representation.
 * Tracks bytes allocated, size of heap, number of lists,
 * and the sublists for each degree.
 */
typedef struct t_Rep {
  size_t allocated;
  size_t size;
  int listCount;
  DegreeList lists; // Degree decreasing with index
} *Rep;

/**
 * Assist Functions
 */

/**
 * Typecast FreeList object to internal representaiton type.
 * 
 * Parameters:
 * - FreeList f -> FreeList object.
 * 
 * Returns:
 * Internal representation.
 * 
 * Errors:
 * - f is NULL.
 */
static Rep rep(FreeList f) {
  if (!f) ERROR("zero pointer");
  return (Rep)f;
}

/**
 * Get the sublist of a given degree.
 * 
 * Does not check for bounds, expects caller does.
 * 
 * Parameters:
 * - Rep r -> Internal rep.
 * - int e -> Degree of sublist.
 * - int l -> Lower bound of freelist.
 * 
 * Returns:
 * Degree list of given degree.
 */
static inline DegreeList get_list(Rep r, int e, int l) {
  return r->lists + (r->listCount + l - 1 - e);
}

/**
 * Get the upper bound given a lower bound.
 * 
 * Parameters:
 * - Rep r -> Internal rep.
 * - int l -> Lower bound of freelist.
 * 
 * Returns:
 * Upper bound of freelist.
 */
static inline int get_u(Rep r, int l) {
  return r->listCount + l - 1;
}

/**
 * Initialize the top level freeblocks of the freelist.
 * No base address is given during creation so this is done
 * whenever alloc detects that there are no bytes allocated
 * in the heap yet.
 * 
 * Parameters:
 * - Rep   r    -> Internal rep.
 * - void *base -> Base address of the heap.
 * - int   l    -> Lower bound of the freelist.
 */
static void init_freeblock_list(Rep r, void *base, int l) {
  FreeBlock block = (FreeBlock)base;
  size_t stride = e2size(r->listCount + l - 1);
  void *bound = base + r->size;

  r->lists->head = block;

  FreeBlock next = (FreeBlock)base;
  while ((void *)next < bound) {
    next = (FreeBlock)((void *)block + stride);
    if ((void *)next >= bound)
      block->next = NULL;
    else
      block->next = next;
    block = next;
  }
}

/**
 * Split a freeblock. Will pop off the next
 * freeblock of a given degree and split it,
 * appending the two child blocks to the sublist
 * below it.
 * 
 * Parameters:
 * - Rep r -> Internal rep.
 * - int e -> Degree of block to split.
 * - int l -> Lower bound of freelist.
 * 
 * Errors:
 * - No block is available to split.
 */
static void split_block(Rep r, int e, int l) {
  // Pop the next freeblock off of e list
  DegreeList list = get_list(r, e, l);
  FreeBlock sb = list->head;
  if (!sb) ERROR("No block available");
  list->head = sb->next;
  
  // Push two new blocks to e - 1 list
  list = get_list(r, e - 1, l);
  FreeBlock tail = list->head;
  list->head = sb;
  FreeBlock bb = (FreeBlock)((void *)sb + e2size(e - 1));
  sb->next = bb;
  bb->next = tail;
}

/**
 * Checks if a sublist contains a given block.
 * 
 * Parameters:
 * - Rep       r -> Internal rep.
 * - FreeBlock b -> Freeblock to look for.
 * - int       e -> Degree of freeblock.
 * - int       l -> Lower bound of freelist.
 * 
 * Returns:
 * 1 if block has been found. 0 otherwise.
 * 
 * Warnings:
 * - Given freeblock is NULL. Will return 0.
 */
static int has_block(Rep r, FreeBlock b, int e, int l) {
  if (b == NULL) {
    WARN("Checking if null block is free.");
    return 0;
  }

  FreeBlock current = get_list(r, e, l)->head;
  while (current != b && current != NULL) {
    current = current->next;
  }
  return current == b;
}

/**
 * Remove a block from the freelist.
 * 
 * Parameters:
 * - Rep       r -> Internal rep.
 * - FreeBlock b -> Freeblock to remove.
 * - int       e -> Degree of freeblock.
 * - int       l -> Lower bound of freelist.
 */
static void remove_block(Rep r, FreeBlock b, int e, int l) {
  if (b == NULL) {
    WARN("Trying to remove null from free block list.");
    return;
  }

  FreeBlock current = get_list(r, e, l)->head;
  if (current == b) {
    // I won't both making another variable to store the list just for this edge case
    get_list(r, e, l)->head = current->next;
    return;
  }

  while (current->next != b && current->next != NULL) current = current->next;

  if (current->next == b) current->next = current->next->next;
}

/**
 * Coalesce two buddies into a block with a higher degree.
 * 
 * Parameters:
 * - Rep       r    -> Internal rep.
 * - void     *base -> Heap base address.
 * - FreeBlock b1   -> The buddy with the lower address.
 * - int       e    -> Degree of buddy.
 * - int       l    -> Lower bound of freelist.
 * 
 * Returns:
 * FreeBlock created from coalescing.
 */
static FreeBlock coalesce_block(Rep r, void *base, FreeBlock b1, int e, int l) {
  FreeBlock b2 = baddrset(base, b1, e);

  remove_block(r, b1, e, l);
  remove_block(r, b2, e, l);
  DegreeList list = get_list(r, e + 1, l);
  b1->next = list->head;
  list->head = b1;
  return b1;
}

/**
 * FreeList Methods
 */

extern FreeList freelistcreate(size_t size, int l, int u) {
  if (l > u) {
    ERROR("Lower bound must be less than or equal to upper bound.");
  }

  if (l < size2e(sizeof(struct t_FreeBlock))) {
    ERROR("l is too small given implementation.");
  }

  size_t maxBlockSize = e2size(u);
  if (size < maxBlockSize) {
    ERROR("Not enough space for maximum block size.");
  }

  if (size % maxBlockSize > 0) {
    WARN("Space is being wasted. use size that is k2^u, where k is a natural number.");
  }

  int listCount = u - l + 1;
  // Trying to make it a bit more dense for the crappy allocations.
  Rep r = (Rep) mmalloc(sizeof(struct t_Rep) + sizeof(struct t_DegreeList) * listCount);
  if (!r) {
    ERROR("Failed to allocate freelist.");
  }
  
  // Construct freelist
  r->allocated = 0;
  r->size = size;
  r->listCount = listCount;
  r->lists = (DegreeList)((void *)r + sizeof(struct t_Rep));
  DegreeList list;
  for (int e = l; e <= u; ++e) {
    list = get_list(r, e, l);
    list->map = bbmcreate(size, e);
    list->head = NULL;
  }

  return r;
}

extern void freelistdelete(FreeList f, int l, int u) {
  Rep r = rep(f);
  
  for (int i = 0; i < r->listCount; ++i) {
    bbmdelete((r->lists + i)->map);
  }
  mmfree(r, sizeof(struct t_Rep) + sizeof(struct t_DegreeList) * r->listCount);
}

extern void *freelistalloc(FreeList f, void *base, int e, int l) {
  Rep r = rep(f);
  if (e < l) {
    WARN("Block size too small.");
    e = l;
  }

  if (e > get_u(r, l)) {
    ERROR("No block size big enough.");
  }

  DegreeList targetList = get_list(r, e, l);
  
  // If unused, assume freeblock list hasn't been established.
  if (r->allocated == 0) {
    init_freeblock_list(r, base, l);
  }

  // Find closest block with degree e.
  int u = get_u(r, l);
  int currentDegree = e;
  while (get_list(r, currentDegree, l)->head == NULL && currentDegree <= u) {
    ++currentDegree;
  }
  
  if (currentDegree > u) {
    // No valid blocks available
    return NULL;
  }

  // Split closest block until arrived to degree e.
  while (currentDegree > e) {
    split_block(r, currentDegree, l);
    --currentDegree;
  }

  // Pop block list, update bitmap, return block pointer.
  FreeBlock b = targetList->head;
  targetList->head = b->next;
  bbmset(targetList->map, base, b, e);
  r->allocated += e2size(e);

  return b;
}

extern void freelistfree(FreeList f, void *base, void *mem, int e, int l) {
  Rep r = rep(f);
  if (e < l) {
    ERROR("Block size too small.");
  }

  if (e > get_u(r, l)) {
    ERROR("No block size big enough.");
  }

  DegreeList list = get_list(r, e, l);
  FreeBlock b1 = (FreeBlock)mem;
  b1->next = list->head;
  list->head = b1;

  // If buddy is free, coalesce blocks, reassign b1 and b2, repeat.
  int u = get_u(r, l);
  int degree = e;
  FreeBlock b2 = baddrinv(base, b1, e);
  while (degree <= u && has_block(r, b2, degree, l)) {
    // We want to continue to clear the bitmap, but we also want
    // to avoid coalescing once we reach u degree.
    bbmclr(get_list(r, degree, l)->map, base, b1, degree);
    if (degree < u) {
      b1 = coalesce_block(r, base, b1 < b2 ? b1 : b2, degree, l);
      b2 = baddrinv(base, b1, degree + 1);
    }
    ++degree;
  }

  r->allocated -= e2size(e);
}

extern int freelistsize(FreeList f, void *base, void *mem, int l, int u) {
  Rep r = rep(f);
  
  int e = l;
  while (e <= u && !bbmtst(get_list(r, e, l)->map, base, mem, e)) {
    ++e;
  }

  return e > u ? -1 : e;
}

extern void freelistprint(FreeList f, void *base, int l, int u) {
  Rep r = rep(f);

  printf("--- Free List ---\n");
  printf("Size:\t%lu bytes\n", r->size);
  printf("\n");
  DegreeList list;
  for (int e = u; e >= l; --e) {
    list = get_list(r, e, l);
    printf("Degree [%2d]\n- bitmap: ", e);
    bbmprt(list->map);
    printf("- list: ");
    FreeBlock b = list->head;
    while (b != NULL) {
      printf("0x%04x -> ", (unsigned int)((void *)b - base));
      b = b->next;
    }
    printf("NULL\n");
  }
}