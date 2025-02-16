#ifndef FREELIST_H
#define FREELIST_H

/**
 * FreeList handles where unallocated and allocated blocks of memory
 * are in the memory bool for the buddy allocator. It handles splitting,
 * merging, allocating, and freeing blocks in the pool.
 */

#include <stdio.h>

typedef void *FreeList;

/**
 * Create a freelist.
 * 
 * Freelist will manage heap memory blocks, each with a size of 2^e,
 * where e is bounded by a lower (l) and upper (u) bound.
 * 
 * The freelist does not allocate the heap.
 * 
 * Parameters:
 * - size_t size -> Overall size of the heap.
 * - int    l    -> Lower bound of degree for block size.
 *      Must be greater than or equal to 3 and less than
 *      or equal to u.
 * - int    u    -> Upper bound of the degree. Must result
 *      in a block size less than or equal to the overall
 *      heap size.
 * 
 * Returns:
 * FreeList object.
 * 
 * Warnings:
 * - Size and choice of upper bound results in wasted space. It
 *      will fill the available space with as many u degree blocks
 *      as possible.
 * 
 * Errors:
 * - Lower bound is larger that upper bound.
 * - Lower bound is too small for implementation.
 * - Size is too small for given upper bound.
 * - Failed to allocate space for freelist memory.
 */
extern FreeList freelistcreate(size_t size, int l, int u);

/**
 * Delete the freelist.
 * 
 * TODO: Remove parameters?
 * Parameters:
 * - int l -> Lower bound block degree.
 * - int u -> Upper bound block degree.
 */
extern void     freelistdelete(FreeList f, int l, int u);

/**
 * Allocate a block from the freelist. Will automatically
 * split larger blocks to create block of desired degree.
 * 
 * Parameters:
 * - FreeList f    -> FreeList object.
 * - void    *base -> Base address of the heap.
 * - int      e    -> Degree of block to allocate.
 * - int      l    -> Lower bound of the freelist.
 * 
 * Returns:
 * Address of allocated space. Will return NULL if unable
 * to allocate block.
 * 
 * Warnings:
 * - Requested degree is too small for lower bound. Will
 *      allocate lower bound block.
 * 
 * Errors:
 * - Requested degree is too large.
 */
extern void *freelistalloc(FreeList f, void *base, int e, int l);

/**
 * Free a block to be reused.
 * 
 * Parameters:
 * - FreeList f    -> FreeList object.
 * - void    *base -> Base heap address.
 * - void    *mem  -> Memory address of block to free.
 * - int      e    -> Degree of block.
 * - int      l    -> Lower bound of the freelist.
 * 
 * Errors:
 * - Block size is too small.
 * - Block size is too large.
 */
extern void  freelistfree(FreeList f, void *base, void *mem, int e, int l);

/**
 * Get the size of an allocated block.
 * 
 * Parameters:
 * - FreeList f    -> FreeList object.
 * - void    *base -> Base heap address.
 * - void    *mem  -> Memory address of the block.
 * - int      l    -> Lower bound of the freelist.
 * - int      u    -> Upper bound of the freelist.
 * 
 * Returns:
 * Degree of the allocated block.
 */
extern int freelistsize(FreeList f, void *base, void *mem, int l, int u);

/**
 * Get the minimum degree of block that can be stored in the freelist.
 * 
 * Returns:
 * Minimum block degree.
 */
extern int freelistmindegree();

/**
 * Prints debugging information about the freelist.
 * 
 * FreeList block addresses will be subtracted by the provided
 * base address for convenience.
 * 
 * Parameters:
 * - FreeList f    -> FreeList object.
 * - void    *base -> Base address to show block addressed from.
 * - int      l    -> Lower bound of freelist.
 * - int      u    -> Upper bound of freelist.
 */
extern void freelistprint(FreeList f, void *base, int l, int u);

#endif
