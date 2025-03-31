#include "mtq.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"

/* Internal Mtq representation */
typedef struct mtq_rep_t {
  Deq q;
  unsigned int max_capacity;
  pthread_mutex_t mutex;
  pthread_cond_t get_cond;
} * MtqRep;

extern Mtq mtq_new(unsigned int max_capacity) {
  MtqRep r = (MtqRep)malloc(sizeof(struct mtq_rep_t));
  r->q = deq_new();
  r->max_capacity = max_capacity;
  pthread_mutex_init(&r->mutex, NULL);
  pthread_cond_init(&r->get_cond, NULL);
  return r;
}

extern void mtq_del(Mtq q, DeqMapF map) {
  if (!q)
    return;
  MtqRep r = (MtqRep)q;
  pthread_cond_destroy(&r->get_cond);
  pthread_mutex_destroy(&r->mutex);
  deq_del(r->q, map);
  free(r);
}

extern void mtq_put(Mtq q, Data d) {
  if (!q)
    ERROR("Mtq is null");
  if (!d)
    ERROR("Data cannot be null");
  MtqRep r = (MtqRep)q;
  pthread_mutex_lock(&r->mutex);
  if (r->max_capacity != 0) {
    while (deq_len(r->q) >= r->max_capacity)
      pthread_cond_wait(&r->get_cond, &r->mutex);
  }
  deq_tail_put(r->q, d);
  pthread_mutex_unlock(&r->mutex);
}

extern Data mtq_get(Mtq q) {
  if (!q)
    ERROR("Mtq is null");
  MtqRep r = (MtqRep)q;
  Data res = NULL;
  pthread_mutex_lock(&r->mutex);
  if (deq_len(r->q) > 0)
    res = deq_head_get(r->q);
  pthread_mutex_unlock(&r->mutex);
  if (res) {
    pthread_cond_signal(&r->get_cond);
  }
  return res;
}

