#ifndef MTQ_H
#define MTQ_H

#include "deq/deq.h"

typedef void *Mtq;

extern Mtq mtq_new(unsigned int max_capacity);
extern void mtq_del(Mtq q, DeqMapF map);

extern void mtq_put(Mtq q, Data d);
extern Data mtq_get(Mtq q);

#endif