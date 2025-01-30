#include "utils.h"

// Borken on my mac. Needed for MAP_ANONYMOUS macro.
#ifndef __USE_MISC
#define __USE_MISC
#endif

#include <sys/mman.h>
#include <error.h>

#include "error.h"

static size_t allocated = 0;
static size_t freed = 0;

extern void *mmalloc(size_t size) {
  void *addr = mmap(
    NULL, size,
    PROT_READ | PROT_WRITE,
    MAP_PRIVATE | MAP_ANON,
    -1, 0
  );
  if (addr != MAP_FAILED) {
    allocated += size;
    return addr;
  }
  return NULL;
  // return addr == MAP_FAILED ? NULL : addr;
}

extern void mmfree(void *p, size_t size) {
  if (munmap(p, size) == -1) {
    ERROR("Failed to free memory");
  }
  freed += size;
}

extern size_t divup(size_t n, size_t d) {
  if (n == 0) return 0;
  return (n + d - 1) / d;
}

extern size_t bits2bytes(size_t bits) {
  return divup(bits, bitsperbyte);
}

extern size_t e2size(int e) {
  return 1 << e;
}

extern int size2e(size_t size) {
  if (size == 0) ERROR("Size of 0 has undefined behavior");
  int e;
  --size;
  for (e = 0; size > 0; ++e) size >>= 1;
  return e;
}

extern void bitset(void *p, int bit) {
  if (bit < 0 || bit >= bitsperbyte) return;
  *(unsigned char *)p |= 1 << bit;
}

extern void bitclr(void *p, int bit) {
  if (bit < 0 || bit >= bitsperbyte) return;
  *(unsigned char *)p &= ~(1 << bit);
}

extern void bitinv(void *p, int bit) {
  if (bit < 0 || bit >= bitsperbyte) return;
  *(unsigned char *)p ^= 1 << bit;
}

extern int bittst(void *p, int bit) {
  if (bit < 0 || bit >= bitsperbyte) return 0;
  return *(unsigned char *)p & 1 << bit;
}

extern void test_leak_report(void) {
  printf("\n[ mmalloc and mmfree report ]\n");
  printf("Allocated: %lu bytes\n", allocated);
  printf("Freed:     %lu bytes\n", freed);

  if (allocated != freed) ERROR("Memory leak detected");
  reset_leak_report();
  printf("\n");
}

extern void reset_leak_report(void) {
  allocated = 0;
  freed = 0;
}
