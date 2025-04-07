#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "lawn.h"
#include "mole.h"
#include "mtq.h"

/* Maximum capacity for the Mtq */
static const unsigned int MAX_CAPACITY = 4;

/**
 * Produces a mole to be wacked. Grabs the Lawn
 * and Mtq from the args, which is an array of
 * void pointers.
 */
static void *produce(void *args) {
  void **t_args = (void **)args;
  Mtq q = (Mtq)t_args[0];
  Lawn l = (Lawn)t_args[1];
  mtq_put(q, (Data)mole_new(l, 0, 0));
  return NULL;
}

/**
 * Consumes a mole. Grabs the Mtq from the
 * args, which is an array of void pointers.
 */
static void *consume(void *args) {
  void **t_args = (void **)args;
  Mtq q = (Mtq)t_args[0];
  Mole m = mtq_get(q);
  mole_whack(m);
  return NULL;
}

int main() {
  srandom(time(0));
  const int n = 10;
  // Setup threads
  pthread_t produce_tids[n];
  pthread_t consume_tids[n];
  Mtq q = mtq_new(MAX_CAPACITY);
  Lawn lawn = lawn_new(0, 0);
  // Load arguments to threads
  void *t_args[2];
  t_args[0] = (void *)q;
  t_args[1] = (void *)lawn;
  // Create produce and consume threads
  for (int i = 0; i < n; i++) {
    pthread_create(&produce_tids[i], NULL, produce, t_args);
    pthread_create(&consume_tids[i], NULL, consume, t_args);
  }
  // Join threads
  for (int i = 0; i < n; i++) {
    pthread_join(produce_tids[i], NULL);
    pthread_join(consume_tids[i], NULL);
  }
  // Cleanup
  lawn_free(lawn);
  mtq_del(q, NULL);
}
