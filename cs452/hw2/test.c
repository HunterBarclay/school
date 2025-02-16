/**
 * File: test.c
 * Author: Jim Buffenbarger
 * 
 * Testing file for the buddy allocator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error.h"
#include "utils.h"
#include "bbm.h"
#include "freelist.h"
#include "balloc.h"

/**
 * Exit upon statement being false.
 */
#define ASSERT(x) do {                                          \
  if (!(x)) {                                                   \
    fprintf(stderr, "[ASSERTION] %s:%d\n", __FILE__, __LINE__); \
    fflush(stderr);                                             \
    exit(1);                                                    \
  }                                                             \
} while (0)                                                     \

static unsigned char HEAP_2048[2048];

static int passed = 0;
static int failed = 0;

void run_test(const char *name, void(*func)(void)) {
  int pid = fork();
  if (pid != 0) {
    // parent process
    int stat;
    waitpid(pid, &stat, 0);
    int normalAdnormal = WIFEXITED(stat);
    int exitCode = WEXITSTATUS(stat);
    if (normalAdnormal != 0 && exitCode == 0) {
      ++passed;
      printf("\033[92;1m[PASS]\033[0m %s\n", name);
    } else {
      ++failed;
      printf("\033[91;1m[FAIL]\033[0m (%d) %s\n", exitCode, name);
    }
  } else {
    func();
    exit(0);
  }
}

/**
 * "utils" Unit Tests.
 */

static void test_utils_mmalloc_mmfree(void) {
  static const size_t size = 4096;

  unsigned char *ptr = (unsigned char *) mmalloc(size);
  ASSERT(ptr != NULL);

  for (size_t i = 0; i < size; ++i) {
    ptr[i] = 5;
  }

  mmfree(ptr, size);
}

static void test_utils_bits2bytes(void) {
  ASSERT(bits2bytes( 0) == 0);
  ASSERT(bits2bytes( 1) == 1);
  ASSERT(bits2bytes( 2) == 1);
  ASSERT(bits2bytes( 3) == 1);
  ASSERT(bits2bytes( 4) == 1);
  ASSERT(bits2bytes( 5) == 1);
  ASSERT(bits2bytes( 6) == 1);
  ASSERT(bits2bytes( 7) == 1);
  ASSERT(bits2bytes( 8) == 1);
  ASSERT(bits2bytes( 9) == 2);
  ASSERT(bits2bytes(10) == 2);
  ASSERT(bits2bytes(16) == 2);
  ASSERT(bits2bytes(17) == 3);
}

static void test_utils_e2size(void) {
  ASSERT(e2size(0) == 1);

  size_t a = 1;
  for (int e = 0; e < 10; ++e) {
    ASSERT(e2size(e) == a);
    a *= 2;
  }
}

static void test_utils_size2e(void) {
  int e = 0;
  size_t lower = 1;
  size_t upper = 1;
  while (e < 10) {
    for (size_t size = lower; size <= upper; ++size) {
      ASSERT(size2e(size) == e);
    }
    lower = upper + 1;
    upper *= 2;
    ++e;
  }
}

static void test_utils_bitset(void) {
  unsigned char a = 0b00110101;
  bitset(&a, 7);
  ASSERT(a == 0b10110101);
  bitset(&a, 1);
  ASSERT(a == 0b10110111);
  bitset(&a, 3);
  ASSERT(a == 0b10111111);
  bitset(&a, 6);
  ASSERT(a == 0b11111111);
}

static void test_utils_bitclr(void) {
  unsigned char a = 0b00110101;
  bitclr(&a, 5);
  ASSERT(a == 0b00010101);
  bitclr(&a, 0);
  ASSERT(a == 0b00010100);
  bitclr(&a, 2);
  ASSERT(a == 0b00010000);
  bitclr(&a, 4);
  ASSERT(a == 0b00000000);
}

static void test_utils_bitinv(void) {
  unsigned char a = 0b00110101;
  bitinv(&a, 6);
  ASSERT(a == 0b01110101);
  bitinv(&a, 5);
  ASSERT(a == 0b01010101);
  bitinv(&a, 4);
  ASSERT(a == 0b01000101);
  bitinv(&a, 4);
  ASSERT(a == 0b01010101);
}

static void test_utils_bittst(void) {
  unsigned char a = 0b00110101;
  ASSERT(!bittst(&a, 6));
  ASSERT(bittst(&a, 5));
  ASSERT(bittst(&a, 4));
  ASSERT(!bittst(&a, 3));
}

/**
 * "freelist" Unit Tests.
 */

static void test_fl_create_delete(void) {
  int u = 10;
  int l = 7;

  FreeList fl = freelistcreate(sizeof(HEAP_2048), l, u);
  freelistdelete(fl, l, u);
}

static void test_fl_alloc_free(void) {
  int u = 10;
  int l = 7;
  FreeList fl = freelistcreate(sizeof(HEAP_2048), l, u);

  /**
   * Create the following map layout:
   * |0x0000         |0x0800
   * +---------------+
   * |a|~| c |   b   |
   * +---------------+
   */
  void *a = freelistalloc(fl, HEAP_2048, 8, l);
  ASSERT(freelistsize(fl, HEAP_2048, a, l, u) == 8);
  ASSERT(a - (void *)HEAP_2048 == 0x0000);
  void *b = freelistalloc(fl, HEAP_2048, 10, l);
  ASSERT(freelistsize(fl, HEAP_2048, b, l, u) == 10);
  ASSERT(b - (void *)HEAP_2048 == 0x0400);
  void *c = freelistalloc(fl, HEAP_2048, 9, l);
  ASSERT(freelistsize(fl, HEAP_2048, c, l, u) == 9);
  ASSERT(c - (void *)HEAP_2048 == 0x0200);
  
  /**
   * Allocate d block and free a:
   * |0x0000         |0x0800
   * +---------------+
   * |~|d| c |   b   |
   * +---------------+
   */
  void *d = freelistalloc(fl, HEAP_2048, 8, l);
  ASSERT(freelistsize(fl, HEAP_2048, d, l, u) == 8);
  ASSERT(d - (void *)HEAP_2048 == 0x0100);
  freelistfree(fl, HEAP_2048, a, freelistsize(fl, HEAP_2048, a, l, u), l);
  
  /**
   * Reallocate a and verify:
   * |0x0000         |0x0800
   * +---------------+
   * |a|d| c |   b   |
   * +---------------+
   */
  a = freelistalloc(fl, HEAP_2048, 8, l);
  ASSERT(freelistsize(fl, HEAP_2048, a, l, u) == 8);
  ASSERT(a - (void *)HEAP_2048 == 0x0000);

  /**
   * Free a and d blocks, allocate e and verify:
   * |0x0000         |0x0800
   * +---------------+
   * | e | c |   b   |
   * +---------------+
   */
  freelistfree(fl, HEAP_2048, a, freelistsize(fl, HEAP_2048, a, l, u), l);
  freelistfree(fl, HEAP_2048, d, freelistsize(fl, HEAP_2048, d, l, u), l);
  void *e = freelistalloc(fl, HEAP_2048, 9, l);
  ASSERT(freelistsize(fl, HEAP_2048, e, l, u) == 9);
  ASSERT(e - (void *)HEAP_2048 == 0x0000);

  freelistdelete(fl, l, u);
}

static void test_fl_size(void) {
  int u = 10;
  int l = 4;
  FreeList fl = freelistcreate(sizeof(HEAP_2048), l, u);

  // Allocate and free a bunch of blocks to start using bitmaps.
  void *a = freelistalloc(fl, HEAP_2048, 4, l);
  void *b = freelistalloc(fl, HEAP_2048, 7, l);
  void *c = freelistalloc(fl, HEAP_2048, 8, l);
  void *d = freelistalloc(fl, HEAP_2048, 5, l);
  void *e = freelistalloc(fl, HEAP_2048, 6, l);
  freelistfree(fl, HEAP_2048, c, 8, l);
  freelistfree(fl, HEAP_2048, e, 6, l);
  freelistfree(fl, HEAP_2048, a, 4, l);
  freelistfree(fl, HEAP_2048, d, 5, l);
  freelistfree(fl, HEAP_2048, b, 7, l);

  // Allocate blocks at degree 9 and 10 to ensure lower lists don't interfere.
  void *f = freelistalloc(fl, HEAP_2048, 9, l);
  void *g = freelistalloc(fl, HEAP_2048, 9, l);
  void *h = freelistalloc(fl, HEAP_2048, 10, l);
  ASSERT(freelistsize(fl, HEAP_2048, f, l, u) == 9);
  ASSERT(freelistsize(fl, HEAP_2048, g, l, u) == 9);
  ASSERT(freelistsize(fl, HEAP_2048, h, l, u) == 10);

  freelistdelete(fl, l, u);
}

/**
 * "balloc" Unit Tests.
 */

static void test_balloc_create_delete(void) {
  Balloc b = bcreate(2048, 4, 8);
  bprint(b);
  bdelete(b);
}

static void test_balloc_alloc_free_size(void) {
  Balloc b = bcreate(512, 3, 4);
  int *a = (int *) balloc(b, sizeof(int));
  ASSERT(a != NULL);
  *a = 30;
  ASSERT(bsize(b, a) == 3);

  bfree(b, a);
  bdelete(b);
}

static void test_balloc_overlap(void) {
  Balloc ba = bcreate(256, 3, 8);
  
  int i = 0;
  char *a = balloc(ba, 32);
  for (i = 0; i < 32; ++i) {
    a[i] = 'a';
  }
  char *b = balloc(ba, 32);
  for (i = 0; i < 32; ++i) {
    b[i] = 'b';
  }
  char *c = balloc(ba, 64);
  for (i = 0; i < 64; ++i) {
    c[i] = 'c';
  }
  char *d = balloc(ba, 128);
  for (i = 0; i < 128; ++i) {
    d[i] = 'd';
  }

  for (i = 0; i < 32; ++i) {
    ASSERT(a[i] == 'a');
  }
  for (i = 0; i < 32; ++i) {
    ASSERT(b[i] == 'b');
  }
  for (i = 0; i < 64; ++i) {
    ASSERT(c[i] == 'c');
  }
  for (i = 0; i < 128; ++i) {
    ASSERT(d[i] == 'd');
  }

  bfree(ba, a);
  bfree(ba, b);
  bfree(ba, c);
  bfree(ba, d);
  bdelete(ba);
}

/**
 * Module Unit Tests
 */

static void test_module_utils(void) {
  printf("\n=== Testing Module \"utils\":\n");
  reset_leak_report();

  run_test("utils - mmalloc & mmfree", &test_utils_mmalloc_mmfree);
  run_test("utils - bits2bytes", &test_utils_bits2bytes);
  run_test("utils - e2size", &test_utils_e2size);
  run_test("utils - size2e", &test_utils_size2e);
  run_test("utils - bitset", &test_utils_bitset);
  run_test("utils - bitclr", &test_utils_bitclr);
  run_test("utils - bitinv", &test_utils_bitinv);
  run_test("utils - bittst", &test_utils_bittst);

  test_leak_report();
}

static void test_module_freelist(void) {
  printf("\n=== Testing Module \"freelist\":\n");
  reset_leak_report();

  run_test("freelist - create & delete", &test_fl_create_delete);
  run_test("freelist - alloc & free", &test_fl_alloc_free);
  run_test("freelist - size", &test_fl_size);

  test_leak_report();
}

static void test_module_balloc(void) {
  printf("\n=== Testing Module \"balloc\":\n");
  reset_leak_report();

  run_test("balloc - create & delete", &test_balloc_create_delete);
  run_test("balloc - alloc & free", &test_balloc_alloc_free_size);
  run_test("balloc - overlap", &test_balloc_overlap);

  test_leak_report();
}

int main(int argc, const char **argv) {
  test_module_utils();
  test_module_freelist();
  test_module_balloc();
#if DEQ_TEST
  test_module_deq();
#endif

  printf("Test Results:\n");
  printf("\033[92;1mPassed\033[0m\t%d\n", passed);
  printf("\033[91;1mFailed\033[0m\t%d\n", failed);

  exit(0);
}