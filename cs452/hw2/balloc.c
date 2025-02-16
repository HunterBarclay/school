/**
 * The Balloc is a mostly a convenience wrapper for the freelist.
 * It literally just holds data to fill in the gaps for the user.
 * 
 * Example buddy allocator memory space throughout steps:
 *  0x000   0x100   0x200   0x300   0x400
 * *) |       |       |       |       |
 * 0) |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|
 * 1) |       A       |~~~~~~~~~~~~~~~| <- Allocate e=9 block
 * 2) |       A       |~~~~~~~|~~~~~~~| <- Allocate e=8 block
 * 3) |       A       |   B   |~~~~~~~|
 * 4) |~~~~~~~~~~~~~~~|   B   |~~~~~~~| <- Free A block
 * 5) |~~~~~~~~~~~~~~~|~~~~~~~|~~~~~~~| <- Free B block
 * 6) |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|
 */

#include "balloc.h"

#include <stdlib.h>

#include "freelist.h"
#include "utils.h"
#include "error.h"

/**
 * Internal representaiton of Balloc.
 * 
 * Contains base heap address, upper and lower block bounds,
 * size of heap, and the freelist.
 */
typedef struct t_Rep {
  void *base;
  int l;
  int u;
  unsigned int size;
  FreeList fl;
} *Rep;

/**
 * Typecast Balloc object to internal representaiton type.
 *
 * Parameters:
 * - Balloc b -> Balloc object.
 *
 * Returns:
 * Internal representation.
 *
 * Errors:
 * - b is NULL.
 */
static Rep rep(Balloc b) {
  if (!b)
    ERROR("zero pointer");
  return (Rep)b;
}

extern Balloc bcreate(unsigned int size, int l, int u) {
  Rep r = (Rep)mmalloc(sizeof(struct t_Rep));

  r->fl = freelistcreate(size, l, u);
  r->l = l;
  r->u = u;
  r->size = size;
  r->base = mmalloc(size);

  return r;
}

extern void bdelete(Balloc pool) {
  Rep r = rep(pool);

  freelistdelete(r->fl, r->l, r->u);
  mmfree(r->base, r->size);
  r->base = NULL;
  r->fl = NULL;
}

extern void *balloc(Balloc pool, unsigned int size) {
  Rep r = rep(pool);
  int e = size2e(size);
  int minBlockSize = freelistmindegree();
  if (e < r->l) e = r->l;
  if (e < minBlockSize) e = minBlockSize;
  return freelistalloc(r->fl, r->base, e, r->l);
}

extern void bfree(Balloc pool, void *mem) {
  Rep r = rep(pool);
  freelistfree(r->fl, r->base, mem, freelistsize(r->fl, r->base, mem, r->l, r->u), r->l);
}

extern unsigned int bsize(Balloc pool, void *mem) {
  Rep r = rep(pool);
  return freelistsize(r->fl, r->base, mem, r->l, r->u);
}

extern void bprint(Balloc pool) {
  Rep r = rep(pool);
  printf("[Buddy] u = %d\n", r->u);
  printf("[Buddy] l = %d\n", r->l);
  printf("[Buddy] size = %u\n", r->size);
  freelistprint(r->fl, r->base, r->l, r->u);
}
