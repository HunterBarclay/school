#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

static const int bitsperbyte=8;

/**
 * Allocate blocks using mmap and will grant
 * a specified number of bytes that are private to
 * a given process and aren't backed by a file. The
 * allocated space will be page aligned, meaning it
 * will consume memory in the order of pages.
 * 
 * The onyx server using 4kb (4096 byte) pages,
 * meaning each mmalloc call will allocate the
 * minimum of 4096k bytes, where k is a natural
 * number, that can contain the specified size.
 * 
 * Successfully allocated bytes will be tracked.
 * 
 * Parameters:
 * - size_t size -> Requested bytes to allocate.
 * 
 * Returns:
 * Memory address to allocated space. NULL if unable
 * to allocate.
 */
extern void *mmalloc(size_t size);

/**
 * Free a block of memory allocated via mmalloc. Must
 * specify request size of allocated block.
 * 
 * Freed bytes will be tracked.
 * 
 * Parameters:
 * - void  *p    -> Memory address of alllocated block.
 * - size_t size -> Originally requested size of allocated block.
 * 
 * Errors:
 * - Failed to free memory.
 */
extern void mmfree(void *p, size_t size);

/**
 * Ceiling of division operation. Safety check for denominator of 0.
 * 
 * Parameters:
 * - size_t n -> Numerator.
 * - size_t d -> Demoninator.
 * 
 * Returns:
 * Ceiling of division of n / d.
 */
extern size_t divup(size_t n, size_t d);
/**
 * Get number of bytes for a given amount of bits.
 * 
 * Parameters:
 * - size_t bits -> Number of bits.
 * 
 * Returns:
 * Number of bytes required to store bits.
 */
extern size_t bits2bytes(size_t bits);

/**
 * 2 to the power of e. Used for getting buddy allocator
 * block size given degree (e) of block.
 * 
 * Parameters:
 * - int e -> Exponent.
 * 
 * Returns:
 * 2^e.
 */
extern size_t e2size(int e);
/**
 * ceiling of log base 2. Used for getting the degree of a
 * a buddy allocator block in order to store size number of bytes.
 * 
 * Parameters:
 * - size-t size -> Number of bytes.
 * 
 * Returns:
 * ceiling of log_2(size).
 * 
 * Errors:
 * - Size is zero, resulting in undefined behavior.
 */
extern int size2e(size_t size);

/**
 * Set the bit of a given byte. Bits are
 * indexed from right to left, meaning:
 * b0000 -> Set bit 0 -> b0001
 * 
 * Will do nothing if bit exceeds 7 or is less than 0.
 * 
 * Parameters:
 * - void *p   -> Pointer to byte.
 * - int   bit -> Bit to set.
 */
extern void bitset(void *p, int bit);
/**
 * Clear the bit of a given byte. Bits are
 * indexed from right to left, meaning:
 * b1111 -> Clear bit 0 -> b1110
 * 
 * Will do nothing if bit exceeds 7 or is less than 0.
 * 
 * Parameters:
 * - void *p   -> Pointer to byte.
 * - int   bit -> Bit to clear.
 */
extern void bitclr(void *p, int bit);
/**
 * Invert the bit of a given byte. Bits are
 * indexed from right to left, meaning:
 * b1010 -> Invert bit 0 -> b1011
 * 
 * Will do nothing if bit exceeds 7 or is less than 0.
 * 
 * Parameters:
 * - void *p   -> Pointer to byte.
 * - int   bit -> Bit to invert.
 */
extern void bitinv(void *p, int bit);
/**
 * Test the bit of a given byte. Bits are
 * indexed from right to left, meaning:
 * b0000 -> Set bit 0 -> b0001
 * 
 * Parameters:
 * - void *p   -> Pointer to byte.
 * - int   bit -> Bit to test.
 * 
 * Returns:
 * 1 if bit is set. 0 otherwise, including if bit is out of range.
 */
extern int  bittst(void *p, int bit);

/**
 * Test the leak report. Allocations and frees are tracked.
 * This will print a report of the number of bytes allocated
 * and freed since the last reset and fail if they don't match.
 * 
 * Will reset counters after test.
 * 
 * Errors:
 * - Allocated and Freed bytes aren't equal.
 */
extern void test_leak_report(void);
/**
 * Reset the allocated and freed bytes counters.
 */
extern void reset_leak_report(void);

#endif
