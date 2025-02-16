/**
 * File: wrapper.c
 * Author: Jim Buffenbarger
 * 
 * Override malloc and free to use buddy allocator.
 */

#include <string.h>

#include "balloc.h"

static Balloc bp=0;

#include <stdio.h>

extern void *malloc(size_t size) {
  bp=bp ? bp : bcreate(4096,4,12);
  return balloc(bp,size);
}

extern void free(void *ptr) {
  bfree(bp,ptr);
}

static size_t min(size_t x, size_t y) { return x < y ? x : y; }

extern void *realloc(void *ptr, size_t size) {
  void *new=malloc(size);
  if (!ptr)
    return new;
  memcpy(new,ptr,min(size,bsize(bp,ptr)));
  free(ptr);
  return new;
}