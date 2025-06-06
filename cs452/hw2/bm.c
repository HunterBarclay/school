#include <stdlib.h>
#include <string.h>

#include "bm.h"
#include "utils.h"

/**
 * Get number of bits in bitmap.
 * 
 * Parameters:
 * - BM b -> Bitmap object.
 * 
 * Returns:
 * Number of bits in bitmap.
 */
static size_t bmbits(BM b) { size_t *bits=b; return *--bits; }

/**
 * Get number of bytes in bitmap.
 * 
 * Parameters:
 * - BM b -> Bitmap object.
 * 
 * Returns:
 * Number of bytes in bitmap.
 */
static size_t bmbytes(BM b) { return bits2bytes(bmbits(b)); }

/**
 * Determine if bit index is within bitmap bounds.
 * 
 * Parameter:
 * - BM     b -> Bitmap object.
 * - size_t i -> Bit index.
 * 
 * Errors:
 * - Index out of bounds.
 */
static void ok(BM b, size_t i) {
  if (i<bmbits(b))
    return;
  fprintf(stderr,"bitmap index out of range\n");
  exit(1);
}

extern BM bmcreate(size_t bits) {
  size_t bytes=bits2bytes(bits);
  size_t *p=mmalloc(sizeof(size_t) + bytes);
  if ((long)p==-1)
    return 0;
  *p=bits;
  BM b=++p;
  memset(b,0,bytes);
  return b;
}

extern void bmdelete(BM b) {
  size_t *p=b;
  p--;
  mmfree(p, sizeof(size_t) + bits2bytes(*p));
}

extern void bmset(BM b, size_t i) {
  ok(b,i); bitset(b+i/bitsperbyte,i%bitsperbyte);
}

extern void bmclr(BM b, size_t i) {
  ok(b,i); bitclr(b+i/bitsperbyte,i%bitsperbyte);
}

extern int bmtst(BM b, size_t i) {
  ok(b,i); return bittst(b+i/bitsperbyte,i%bitsperbyte);
}

extern void bmprt(BM b) {
  for (int byte=bmbytes(b)-1; byte>=0; byte--)
    printf("%02x%s",((char *)b)[byte],(byte ? " " : "\n"));
}
