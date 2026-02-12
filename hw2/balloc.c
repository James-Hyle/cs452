#include "balloc.h"

Balloc bcreate(unsigned int size, int l, int u) {
  int guardUp = e2size(u);
  if (guardUp > size)
    return NULL;

  Block *block = mmalloc(sizeof(Block));
  if (!block)
    return NULL;

  block->blockSize = size;
  block->lower = l;
  block->upper = u;
  block->address = mmalloc(size);
  block->free_lists = freelistcreate(size, l, u);

  int num_slots = size / (1 << l);
  block->tag = mmalloc(num_slots);
  for (int i = 0; i < num_slots; i++)
    block->tag[i] = 0;

  int num_levels = u - l + 1;
  block->bbm = mmalloc(num_levels * sizeof(BBM));
  for (int i = 0; i < num_levels; i++) {
    block->bbm[i] = bbmcreate(size, l + i);
  }

  freelistfree(block->free_lists, block->address, block->address, u, l);
  return block;
}

void bdelete(Balloc pool) {
  if (!pool)
    return;

  Block *p = (Block *)pool;
  int num_levels = p->upper - p->lower + 1;

  for (int i = 0; i < num_levels; i++) {
    bbmdelete(p->bbm[i]);
  }

  freelistdelete(p->free_lists, p->lower, p->upper);

  mmfree(p->bbm, num_levels * sizeof(BBM));
  mmfree(p->address, p->blockSize);
  mmfree(p->tag, p->blockSize / (1 << p->lower));
  mmfree(p, sizeof(Block));
}

void *balloc(Balloc pool, unsigned int size) {
  if (!pool || size == 0)
    return NULL;
  Block *p = (Block *)pool;
  int e = size2e(size);
  if (e < p->lower)
    e = p->lower;
  if (e > p->upper)
    return NULL;

  for (int i = e; i <= p->upper; i++) {
    void *block = freelistalloc(p->free_lists, p->address, i, p->lower);
    if (block) {
      int current_e = i;
      while (current_e > e) {
        current_e--;
        void *buddy = baddrinv(p->address, block, current_e);
        freelistfree(p->free_lists, p->address, buddy, current_e, p->lower);
      }

      int slot = ((char *)block - (char *)p->address) >> p->lower;
      p->tag[slot] = (unsigned char)e;

      bbmset(p->bbm[e - p->lower], p->address, block, e);
      return block;
    }
  }
  return NULL;
}

void bfree(Balloc pool, void *mem) {
  if (!pool || !mem)
    return;
  Block *p = (Block *)pool;

  unsigned int sz = bsize(pool, mem);
  if (sz == 0)
    return;

  int e = size2e(sz);
  void *block = mem;

  int slot = ((char *)block - (char *)p->address) >> p->lower;
  p->tag[slot] = 0;

  bbmclr(p->bbm[e - p->lower], p->address, block, e);

  while (e < p->upper) {
    void *buddy = baddrinv(p->address, block, e);
    int idx = e - p->lower;

    if (bbmtst(p->bbm[idx], p->address, buddy, e))
      break;

    void **lists = (void **)p->free_lists;
    void **prev = &lists[idx];
    void *curr = lists[idx];
    int found = 0;
    while (curr) {
      if (curr == buddy) {
        *prev = *(void **)curr;
        found = 1;
        break;
      }
      prev = (void **)curr;
      curr = *(void **)curr;
    }

    if (!found)
      break;

    if (buddy < block)
      block = buddy;
    e++;

    if (e < p->upper)
      bbmclr(p->bbm[e - p->lower], p->address, block, e);
  }

  freelistfree(p->free_lists, p->address, block, e, p->lower);
}

unsigned int bsize(Balloc pool, void *mem) {
  Block *p = (Block *)pool;
  if (!mem || mem < p->address || mem >= p->address + p->blockSize)
    return 0;

  int slot = ((char *)mem - (char *)p->address) >> p->lower;
  int e = p->tag[slot];

  return (e == 0) ? 0 : (1U << e);
}

void bprint(Balloc pool) {
  Block *memPool = pool;
  if (!memPool)
    printf("NULL pool");
    printf("\n---allocator State---\n");
    printf("Pool address:    %p\n", memPool);
    printf("Memory address:  %p\n", memPool->address);
    printf("Pool size:       %zu bytes\n", memPool->blockSize);
    printf("lower:\t%d (2^%d = %zu bytes)\n", memPool->lower, memPool->lower,
         e2size(memPool->lower));
    printf("upper:\t%d (2^%d = %zu bytes)\n", memPool->upper, memPool->upper,
         e2size(memPool->upper));

  printf("\n--- free Lists ---\n");
  freelistprint(memPool->free_lists, memPool->lower, memPool->upper);

  printf("\n--- bitmaps ---\n");
  printf("(1 = allocated, 0 = free)\n");
  printf("bbmprt:\n");
  for (int i = 0; i < memPool->upper - memPool->lower + 1; i++) {
    bbmprt(memPool->bbm[i]);
  }

  printf("===========================================\n\n");
  return;
}
