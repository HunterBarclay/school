#ifndef MTQ_H
#define MTQ_H

#include "deq/deq.h"

/* Multi-threaded queue object */
typedef void *Mtq;

/**
 * Creates new Mtq with a maximum_capacity.
 *
 * Set max_capacity to zero to disable it.
 */
extern Mtq mtq_new(unsigned int max_capacity);

/**
 * Deletes a Mtq. map will be used to destroy
 * queue elements, or assign to NULL to do nothing
 * to existing queue elements.
 */
extern void mtq_del(Mtq q, DeqMapF map);

/**
 * Put data into the Mtq.
 */
extern void mtq_put(Mtq q, Data d);

/**
 * Get the next piece of data in the queue. Will
 * return NULL in queue is empty.
 */
extern Data mtq_get(Mtq q);

#endif
