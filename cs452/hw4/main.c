#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "lawn.h"
#include "mole.h"
#include "mtq.h"

static const unsigned int MAX_CAPACITY = 4;

static Mole produce(Lawn l) { return mole_new(l, 0, 0); }
static void consume(Mole m) { mole_whack(m); }

static void *produce(void *args) {
  void **t_args = (void **)args;
  Mtq q = (Mtq)t_args[0];
  Lawn l = (Lawn)t_args[1];
  mtq_put(q, (Data)mole_new(l, 0, 0));
  return NULL;
}

static void *consume(void *args) {
  void **t_args = (void **)args;
  Mtq q = (Mtq)t_args[0];
  Mole m = NULL;
  while (!m)
    m = mtq_get(q);
  mole_whack(m);
  return NULL;
}

int main() {
  srandom(time(0));
  const int n = 10;
  pthread_t produce_tids[n];
  pthread_t consume_tids[n];
  Mtq q = mtq_new(MAX_CAPACITY);
  Lawn lawn = lawn_new(0, 0);
  void *t_args[2];
  t_args[0] = (void *)q;
  t_args[1] = (void *)lawn;
  for (int i = 0; i < n; i++) {
    pthread_create(&produce_tids[i], NULL, produce, t_args);
    pthread_create(&consume_tids[i], NULL, consume, t_args);
  }
  for (int i = 0; i < n; i++) {
    pthread_join(&produce_tids[i], NULL);
    pthread_join(&consume_tids[i], NULL);
  }
  lawn_free(lawn);
  mtq_del(q, NULL);
}
