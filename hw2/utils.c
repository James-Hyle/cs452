#include "utils.h"
#include <sys/mman.h>

void *mmalloc(size_t size) {
  return mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,
              0);
}

void mmfree(void *p, size_t size) {
  munmap(p, size);
}

size_t divup(size_t n, size_t d) {
  return (n + d - 1) / d;
}

size_t bits2bytes(size_t bits) {
  return divup(bits, 8);
}

size_t e2size(int e) {
  size_t ret = 0;
  return ret = 1 << e;
}

int size2e(size_t size) {
  if (size == 0)
    return -1;
  int i = 0;
  size_t orig = size;
  while (size != 1) {
    size >>= 1;
    i++;
  }
  if ((size_t)1 << i < orig)
    i++;
  return i;
}

void bitset(void *p, int bit) {
  size_t *ptr = p;
  *ptr |= (size_t)1 << bit;
}

void bitclr(void *p, int bit) {
  size_t *ptr = p;
  *ptr &= ~((size_t)1 << bit);
}

void bitinv(void *p, int bit) {
  size_t *ptr = p;
  *ptr ^= (size_t)1 << bit;
}

int bittst(void *p, int bit) {
  size_t *ptr = p;
  return (*ptr & (size_t)1 << bit) ? 1 : 0;
}
