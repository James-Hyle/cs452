#include "balloc.h"

Balloc bcreate(unsigned int size, int l, int u) {
  // check if 
  int guardUp = e2size(u);
  if (guardUp > size) return 0;
  // allocate memory for container to hold 
  Block *block = mmalloc(sizeof(Block));
  // guard
  if (!block) return NULL;

  // assign struct fields
  block->blockSize = size;
  block->lower = l;
  block->upper = u;
  block->address = mmalloc(size);

  // calculate order range
  int orders = u - l;

  // allocate memory for free lists and bitmaps
  block->free_lists = mmalloc(orders * sizeof(void *));
  block->bbm = mmalloc(orders * sizeof(BBM));

  // create 
  for (int i = 0; i < orders; i++) {
    block->free_lists[i] = NULL;
    block->bbm[i] = bbmcreate(size, l + i);
  }

  int upperIndex = u - l;
  block->free_lists[upperIndex] = block->address;
  *(void **)(block->address) = NULL;

  return block;
}

void bdelete(Balloc pool) {
  // guard
  if (!pool) return;

  Block *p = (Block *) pool;
  int num_levels = p->upper - p->lower + 1;

  for (int i = 0; i < num_levels; i++) {
    bbmdelete(p->bbm[i]);
  }

  mmfree(p->free_lists, num_levels * sizeof(void *));
  mmfree(p->bbm, num_levels * sizeof(BBM));
  mmfree(p->address, p->blockSize);
  mmfree(p, sizeof(Block));
}

void *balloc(Balloc pool, unsigned int size) {
  Block *p = (Block *)pool;
  int e = size2e(size);
  if (e < p->lower) e = p->lower;

  for (int i = e; i <= p->upper; i++) {
    int idx = i - p->lower;
    if (p->free_lists[idx] != NULL);
  }

  return NULL;
}

void bfree(Balloc pool, void *mem) {
}

unsigned int bsize(Balloc pool, void *mem) {
  if (!pool || !mem) return 0;
  Block *p = (Block *)pool;
  for (int e = p->lower; e < p->upper; e++) {
    if (bbmtst(p->bbm[e], p->address, mem, e))
      return (unsigned int)((size_t)1 << e);
  }

  return ((size_t)1 << p->upper);
}

void bprint(Balloc pool) {
  Block *memPool = pool;
  printf("bprint start:\n");
  printf("address of mempool: %p\n", memPool);
  printf("Size of pool: %d\n", memPool->blockSize);
  printf("Upper Val: %d\n", memPool->upper);
  printf("Lower Val: %d\n", memPool->lower);
}
