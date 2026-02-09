#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

static const int bitsperbyte = 8;

// mmalloc: allocate memory block using mmap()
// size: size of memory block requested
extern void *mmalloc(size_t size);

// mmfree: free memory block using munmap()
// *p: address of mem block to be freed
// size: size of mem block to be freed
extern void mmfree(void *p, size_t size);

// divup: divide memory block
extern size_t divup(size_t n, size_t d);

// bits2bytes:
extern size_t bits2bytes(size_t bits);

// e2size: return size value (unsigned long) converted from exponent value
// e: exponent value
extern size_t e2size(int e);

// size2e: return exponent value converted from size value (unsigned long)
// size: size
extern int size2e(size_t size);

// bitset: bit set in memory address
// *p: memory address
// bit: bit to set
extern void bitset(void *p, int bit);

// bitclr: clear bit in memory address
// *p: memory address
// bit: bit to clear
extern void bitclr(void *p, int bit);

// bitclr: invert bit in memory address
// *p: memory address
// bit: bit to invert
extern void bitinv(void *p, int bit);

// bitclr: return if bit is set at memory address
// *p: memory address
// bit: bit to test
extern int bittst(void *p, int bit);

#endif
