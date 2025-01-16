#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];        // next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];                // head/tail nodes
  int len;
} *Rep;

static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

/**
 * Attempts to put data at a given end of the linked list.
 * 
 * Parameters:
 * - Rep r  -> Doubly-linked list representation.
 * - End e  -> End of the list to append to.
 * - Data d -> Data to append to the list.
 * 
 * Warnings:
 * - Cannot insert NULL.
 * 
 * Errors:
 * - Failure to allocate memory for node.
 */
static void put(Rep r, End e, Data d) {
  // Cannot insert NULL.
  if (!d) {
    WARN("Cannot insert NULL.");
    return;
  }

  // Create and setup new node
  Node node = (Node)malloc(sizeof(*node));
  // Check for allocation
  if (!node)
    ERROR("Failed to allocate node. Out of memory");

  node->data = d;
  node->np[Head] = node->np[Tail] = NULL;

  if (r->len < 1) {
    // If empty, setup head and tail
    r->ht[Head] = r->ht[Tail] = node;
  } else {
    // Else, append it to the start/end
    Node endNode = r->ht[e];
    node->np[1 - e] = endNode;
    endNode->np[e] = node;
    r->ht[e] = node;
  }

  // Increment the size
  ++r->len;
}

/**
 * Gets the ith element in the list from a given end.
 * 
 * Parameters:
 * - Rep r -> Doubly-linked list representation.
 * - End e -> End of the list to index from.
 * - int i -> Index.
 * 
 * Returns:
 * Data at ith index or NULL if not found.
 * 
 * Warnings:
 * - Index (i) out of list bounds.
 */
static Data ith(Rep r, End e, int i)  {
  // Check for bounds
  if (i >= r->len) {
    WARN("Out of bounds");
    return NULL;
  }

  int index = i;
  Node curr = r->ht[e];
  // Go i number of nodes from the chosen end
  while (index > 0 && curr) {
    curr = curr->np[1 - e];
    --index;
  }

  // Returns either data at ith node, or null
  return index == 0 && curr ? curr->data : NULL;
}

/**
 * Pop off the value at a given end of the list.
 * 
 * Parameters:
 * - Rep r -> Doubly-linked list representation.
 * - End e -> End of the list to index from.
 * 
 * Returns:
 * Data at the end of the list. NULL if list is empty.
 */
static Data get(Rep r, End e) {
  // If queue is empty, return null
  if (r->len == 0)
    return NULL;

  // Get the end node, its data, and the node next to it
  Node node = r->ht[e];
  Data data = node->data;
  Node newEnd = node->np[1 - e];
  
  // Setup the next node to become the new end
  if (newEnd)
    newEnd->np[e] = NULL;
  r->ht[e] = newEnd;

  // Decrement length, adjust head and tail nodes
  --r->len;
  if (r->len == 0) {
    r->ht[Head] = r->ht[Tail] = NULL;
  }

  // Free removed node
  free(node);
  return data;
}

/**
 * Remove the first instance of data (d) from a given end from the list.
 * 
 * Parameters:
 * - Rep r  -> Doubly-linked list representation.
 * - End e  -> End of the list to index from.
 * - Data d -> Data to remove.
 * 
 * Returns:
 * Data (d) if found in list and removed; NULL otherwise.
 */
static Data rem(Rep r, End e, Data d) {
  // Iterate through nodes until non are left, or data is found
  Data foundData = NULL;
  Node curr = r->ht[e];
  while (curr && curr->data != d)
    curr = curr->np[1 - e];
  
  // If data is found, remove the node
  if (curr && curr->data == d) {
    Node next = curr->np[Tail];
    Node prev = curr->np[Head];

    if (next)
      next->np[Head] = prev;
    else
      r->ht[Tail] = prev;

    if (prev)
      prev->np[Tail] = next;
    else
      r->ht[Head] = next;

    --r->len;
    if (r->len == 0)
      r->ht[Head] = r->ht[Tail] = NULL;

    // Store data and free removed node
    foundData = curr->data;
    free(curr);
  }

  return foundData;
}

extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head);   }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail);   }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data;
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
