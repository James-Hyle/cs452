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
  int lower;          // lower bound of blocks
  int upper;          // upper bound of
  unsigned char *tag; // array for tags for bitmap management
  void *address;      // address of block
  void **free_lists;  // array of addresses for free lists
  BBM *bbm;           // array of bitmaps
} Block;

// create new memory pool
// size: bytes in mem pool
// l: lower bound exp
// u: upper bound exp
extern Balloc bcreate(unsigned int size, int l, int u);

// free mem pool
// pool: memory block
extern void bdelete(Balloc pool);

// allocate bytes of memory
// pool: memory pool
extern void *balloc(Balloc pool, unsigned int size);

// free memory block
// pool: memory pool
// *mem: pointer to memory block
extern void bfree(Balloc pool, void *mem);

// get size of 
extern unsigned int bsize(Balloc pool, void *mem);

// print out memory pool
extern void bprint(Balloc pool);

#endif
