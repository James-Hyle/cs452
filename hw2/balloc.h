#ifndef BALLOC_H
#define BALLOC_H

#include <stdio.h>

#include "bbm.h"
#include "freelist.h"
#include "utils.h"

typedef void *Balloc;

// struct for memory pool
typedef struct Block {
  size_t blockSize;
  int lower;         // lower bound of blocks
  int upper;         // upper bound of
  void *address;     // address of block
  void **free_lists; // array of addresses for free lists
  BBM *bbm;          // array of bitmaps
} Block;

// bcreate:
extern Balloc bcreate(unsigned int size, int l, int u);

//
extern void bdelete(Balloc pool);

extern void *balloc(Balloc pool, unsigned int size);

extern void bfree(Balloc pool, void *mem);

// bsize: return size of memory pool
// pool: memory pool to operate on
// *mem: 
extern unsigned int bsize(Balloc pool, void *mem);

// bprint: print representation of memory pool to stdout
// pool: memory container
extern void bprint(Balloc pool);

#endif
