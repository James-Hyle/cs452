#include "balloc.h"

#include <stdio.h>
#include <sys/mman.h>

// struct for initial block of memory, upon calling bcreate, balloc allocates chunk for memory pool
typedef struct {
  int blockSize;
  int lower;
  int upper;
  void *address; // points to larger pool of memory
} Block;

extern Balloc bcreate(unsigned int size, int l, int u) {
  int blockSize = size;
  // call mmap for address for chunk of memory to divy out
  Block *block = mmap(0, sizeof(Block), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  block->blockSize = size;
  printf("Size: %d\n", block->blockSize);
  block->lower = l;
  printf("Lower: %d\n", block->lower);
  block->upper = u;
  printf("Upper: %d\n", block->upper);
  
  // if (blockSize) // implement 2^k check
  
  // get pointer to chunk of memory using mmap for larger pool 
  block->address = mmap(0, blockSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  printf("Size of Block-Address for larger pool: %ld bytes\n", sizeof(block->address));
  
  return block;
}

extern void bdelete(Balloc pool) {
}

extern void *balloc(Balloc pool, unsigned int size) {
}

extern void bfree(Balloc pool, void *mem) {
}

extern unsigned int bsize(Balloc pool, void *mem) {
}

extern void bprint(Balloc pool) {
  printf("address of mempool: %p\n", pool);


}
