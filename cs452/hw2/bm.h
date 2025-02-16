#ifndef BM_H
#define BM_H

/**
 * File: bm.h
 * Author: Jim Buffenbarger
 * 
 * Generic, N-length bit map.
 */

#include <stdio.h>

typedef void *BM;

/**
 * Create a bitmask of a given width.
 * 
 * Parameters:
 * - size_t bits -> Number of bits in the mask.
 * 
 * Returns:
 * Bitmask type pointer.
 */
extern BM bmcreate(size_t bits);
/**
 * Delete a bitmask.
 * 
 * Parameters:
 * - BM b -> Bitmask to delete.
 */
extern void bmdelete(BM b);

/**
 * Set a bit on a bitmask.
 * 
 * Parameters:
 * - BM     b -> Target bitmask.
 * - size_t i -> Bit to set.
 */
extern void bmset(BM b, size_t i);
/**
 * Clear a bit on a bitmask.
 * 
 * Parameters:
 * - BM     b -> Target bitmask.
 * - size_t i -> Bit to clear.
 */
extern void bmclr(BM b, size_t i);
/**
 * Test for a bit in a bitmask.
 * 
 * Parameters:
 * - BM     b -> Target bitmask.
 * - size_t i -> Bit to test.
 */
extern int  bmtst(BM b, size_t i);

/**
 * Print the bitmask.
 * 
 * Parameters:
 * - BM b -> Target bitmask.
 */
extern void bmprt(BM b);

#endif
