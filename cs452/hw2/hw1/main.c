#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "deq.h"

/**
 * Test elements to add to the queue
 */
static char* itemA = "A";
static char* itemB = "B";
static char* itemC = "C";
static char* itemD = "D";
static char* itemE = "E";

/**
 * Make sample queue for testing. Contents look like:
 * [ "A", "B", "C" ]
 */
static Deq make_abc(void) {
  Deq q = deq_new();
  deq_tail_put(q, itemA);
  deq_tail_put(q, itemB);
  deq_tail_put(q, itemC);
  return q;
}

/**
 * Test the put method.
 */
static void test_put(void) {
  Deq q = make_abc();

  deq_head_put(q, itemD);
  assert(deq_len(q) == 4);
  assert(deq_tail_ith(q, 3) == itemD);
  deq_tail_put(q, itemE);
  assert(deq_len(q) == 5);
  assert(deq_head_ith(q, 4) == itemE);
  printf("!!! Warning expected !!!\n\n");
  deq_head_put(q, NULL);
  printf("\n!!! Warning should have displayed !!!\n");
  assert(deq_len(q) == 5);

  deq_del(q, NULL);
  printf("Put Passed\n");
}

/**
 * Test the ith method.
 */
static void test_ith(void) {
  Deq q = make_abc();

  assert(deq_head_ith(q, 0) == itemA);
  assert(deq_head_ith(q, 1) == itemB);
  assert(deq_head_ith(q, 2) == itemC);
  assert(deq_tail_ith(q, 0) == itemC);
  assert(deq_tail_ith(q, 1) == itemB);
  assert(deq_tail_ith(q, 2) == itemA);

  deq_head_put(q, itemD);
  assert(deq_head_ith(q, 2) == itemB);
  assert(deq_tail_ith(q, 0) == itemC);

  deq_del(q, NULL);
  printf("Ith Passed\n");
}

/**
 * Test the get method from the head of the queue.
 */
static void test_head_get(void) {
  Deq q = make_abc();

  assert(deq_head_get(q) == itemA);
  assert(deq_len(q) == 2);
  assert(deq_head_get(q) == itemB);
  assert(deq_len(q) == 1);
  assert(deq_head_get(q) == itemC);
  assert(deq_len(q) == 0);
  assert(deq_head_get(q) == NULL);
  assert(deq_len(q) == 0);

  deq_del(q, NULL);
  printf("  Get (head) Passed\n");
}

/**
 * Test the get method from the tail of the queue.
 */
static void test_tail_get(void) {
  Deq q = make_abc();

  assert(deq_tail_get(q) == itemC);
  assert(deq_len(q) == 2);
  assert(deq_tail_get(q) == itemB);
  assert(deq_len(q) == 1);
  assert(deq_tail_get(q) == itemA);
  assert(deq_len(q) == 0);
  assert(deq_tail_get(q) == NULL);
  assert(deq_len(q) == 0);

  deq_del(q, NULL);
  printf("  Get (tail) Passed\n");
}

/**
 * Test the get method. Head and tail.
 */
static void test_get(void) {
  test_head_get();
  test_tail_get();

  printf("Get Passed\n");
}

/**
 * Test the rem method. Removing element "A".
 */
static void test_rem_a(void) {
  Deq q1 = make_abc();
  assert(deq_head_rem(q1, itemA) == itemA);
  assert(deq_len(q1) == 2);

  deq_del(q1, NULL);

  Deq q2 = make_abc();
  assert(deq_tail_rem(q2, itemA) == itemA);
  assert(deq_len(q2) == 2);

  deq_del(q2, NULL);
  printf("  Rem (a) Passed\n");
}

/**
 * Test the rem method. Removing element "B".
 */
static void test_rem_b(void) {
  Deq q1 = make_abc();
  assert(deq_head_rem(q1, itemB) == itemB);
  assert(deq_len(q1) == 2);

  deq_del(q1, NULL);

  Deq q2 = make_abc();
  assert(deq_tail_rem(q2, itemB) == itemB);
  assert(deq_len(q2) == 2);

  deq_del(q2, NULL);
  printf("  Rem (b) Passed\n");
}

/**
 * Test the rem method. Removing element "C".
 */
static void test_rem_c(void) {
  Deq q1 = make_abc();
  assert(deq_head_rem(q1, itemC) == itemC);
  assert(deq_len(q1) == 2);

  deq_del(q1, NULL);

  Deq q2 = make_abc();
  assert(deq_tail_rem(q2, itemC) == itemC);
  assert(deq_len(q2) == 2);

  deq_del(q2, NULL);
  printf("  Rem (c) Passed\n");
}

/**
 * Test the rem method. Removing element not currently in the list.
 */
static void test_rem_fail(void) {
  Deq q1 = make_abc();
  assert(deq_head_rem(q1, itemD) == NULL);
  assert(deq_len(q1) == 3);

  deq_del(q1, NULL);

  Deq q2 = make_abc();
  assert(deq_tail_rem(q2, itemD) == NULL);
  assert(deq_len(q2) == 3);

  deq_del(q2, NULL);
  printf("  Rem (fail) Passed\n");
}

/**
 * Test the rem method.
 */
static void test_rem(void) {
  test_rem_a();
  test_rem_b();
  test_rem_c();
  test_rem_fail();
  printf("Rem Passed\n");
}

/**
 * Test queue methods.
 */
static void test(void) {
  test_put();
  test_ith();
  test_get();
  test_rem();

  printf("All Tests Passed\n\n");
}

int main() {
  // Run tests on the queue.
  test();

  // Create sample queue and test to string to self verfiy contents.
  Deq q=deq_new();

  deq_tail_put(q, "Hello");
  deq_tail_put(q, "World");
  deq_tail_put(q, "!");

  char *s=deq_str(q,0);
  printf("Elements of list (space delimiter):\n[ %s ]\n",s);
  free(s);

  deq_del(q,0);
  return 0;
}