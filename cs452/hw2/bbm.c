#include "bbm.h"
#include "bm.h"
#include "utils.h"

/**
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

static size_t mapsize(size_t size, int e) {
  size_t blocksize=e2size(e);
  size_t blocks=divup(size,blocksize);
  size_t buddies=divup(blocks,2);
  return buddies;
}

/**
 * Get index of buddy bitmap given block description.
 * 
 * Example:
 * Given the relative address of 0x200, and a block degree of 8,
 * It'll first find the first/earliest buddy by clearing that degrees
 * related bit in the relative address,
 * 
 * 0x300 would point to the last/latest block in the second 8th degree buddy pairing,
 * 0x200 would point to the first/earlist block in the second 8th degree buddy pairing.
 * 
 * Next, we then find the bit index in the field by dividing our earliest buddy address by the size, then by two.
 */
static size_t bitaddr(void *base, void *mem, int e) {
  size_t addr=baddrclr(base,mem,e)-base;
  size_t blocksize=e2size(e);
  return addr/blocksize/2;
}

extern BBM bbmcreate(size_t size, int e) {
  size_t mapSize = mapsize(size, e);
  BBM b=bmcreate(mapSize);
  if ((long)b==-1)
    return 0;
  return b;
}

extern void bbmdelete(BBM b) {
  bmdelete(b);
}

extern void bbmset(BBM b, void *base, void *mem, int e) {
  bmset(b,bitaddr(base,mem,e));
}

extern void bbmclr(BBM b, void *base, void *mem, int e) {
  bmclr(b,bitaddr(base,mem,e));
}

extern int bbmtst(BBM b, void *base, void *mem, int e) {
  return bmtst(b,bitaddr(base,mem,e));
}

extern void bbmprt(BBM b) { bmprt(b); }

extern void *baddrset(void *base, void *mem, int e) {
  unsigned int mask=1<<e;
  return base+((mem-base)|mask);
}

extern void *baddrclr(void *base, void *mem, int e) {
  unsigned int mask=~(1<<e);
  return base+((mem-base)&mask);
}

extern void *baddrinv(void *base, void *mem, int e) {
  unsigned int mask=1<<e;
  return base+((mem-base)^mask);
}

extern int baddrtst(void *base, void *mem, int e) {
  unsigned int mask=1<<e;
  return (mem-base)&mask;
}
