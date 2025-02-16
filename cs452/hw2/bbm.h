#ifndef BBM_H
#define BBM_H

/**
 * File: bbm.h
 * Author: Jim Buffenbarger
 * 
 * Buddy Bit Map used for tracking which buddies are allocated.
 */

#include <stdio.h>

typedef void *BBM;

/**
 * Create a 
 * 
 * Parameters:
 * - size_t size -> Size of the bit ma
 */
extern BBM  bbmcreate(size_t size, int e);

extern void bbmdelete(BBM b);

extern void bbmset(BBM b, void *base, void *mem, int e);

extern void bbmclr(BBM b, void *base, void *mem, int e);

extern  int bbmtst(BBM b, void *base, void *mem, int e);

extern void bbmprt(BBM b);

/**
 * Sets bit of memory address, relative to base address.
 * 
 * Parameters:
 * - void *base -> Base memory address.
 * - void *mem  -> Global memory address.
 * - int  e     -> Index of bit to set.
 * 
 * Returns:
 * Modified memory address, converted back to global address space.
 */
extern void *baddrset(void *base, void *mem, int e);

/**
 * Clears bit of memory address, relative to base address.
 * 
 * Parameters:
 * - void *base -> Base memory address.
 * - void *mem  -> Global memory address.
 * - int  e     -> Index of bit to clear.
 * 
 * Returns:
 * Modified memory address, converted back to global address space.
 */
extern void *baddrclr(void *base, void *mem, int e);

/**
 * Inverts bit of memory address, relative to base address.
 * 
 * Parameters:
 * - void *base -> Base memory address.
 * - void *mem  -> Global memory address.
 * - int  e     -> Index of bit to invert.
 * 
 * Returns:
 * Modified memory address, converted back to global address space.
 */
extern void *baddrinv(void *base, void *mem, int e);

/**
 * Tests bit of memory address, relative to base address.
 * 
 * Parameters:
 * - void *base -> Base memory address.
 * - void *mem  -> Global memory address.
 * - int  e     -> Index of bit to clear.
 * 
 * Returns:
 * Test result. 1 if set, 0 if cleared.
 */
extern int   baddrtst(void *base, void *mem, int e);

#endif
