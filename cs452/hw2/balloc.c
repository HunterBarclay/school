#include "balloc.h"

#include <stdlib.h>

extern Balloc bcreate(unsigned int size, int l, int u) { return NULL; }
extern void   bdelete(Balloc pool) { }

extern void *balloc(Balloc pool, unsigned int size) { return NULL; }
extern void  bfree(Balloc pool, void *mem) { }

extern unsigned int bsize(Balloc pool, void *mem) { return 0; }
extern void bprint(Balloc pool) { }
