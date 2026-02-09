#include "utils.h"
#include <sys/mman.h>

// call mmap for chunk of mem address
void *mmalloc(size_t size) {
  return mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

// unmap memory at address
void mmfree(void *p, size_t size) {
  munmap(p, size);
}

size_t divup(size_t n, size_t d) {

}

// convert bits to bytes
size_t bits2bytes(size_t bits) {
  return bits / 8;
}

// convert exponent to size
size_t e2size(int e) {
  size_t ret = 0;
  return ret = 1 << e;
}

// convert int to exponent
int size2e(size_t size) {
  int i = 0;
  while (size != 1) {
    size >>= 1;
    i++;
  }
  return i;
}

// set bit at address
void bitset(void *p, int bit) {
  size_t *ptr = p;
  *ptr |= (size_t)1 << bit;
}

// clear bit at address
void bitclr(void *p, int bit) {
  size_t *ptr = p;
  *ptr &= ~((size_t)1 << bit);
}

// invert bit at address
void bitinv(void *p, int bit) {
  size_t *ptr = p;
  *ptr ^= (size_t)1 << bit;
}

// test bit at address
int bittst(void *p, int bit) {
  size_t *ptr = p;
  return (*ptr & (size_t)1 << bit) ? 1 : 0;
}
