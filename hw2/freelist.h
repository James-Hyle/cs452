#ifndef FREELIST_H
#define FREELIST_H

#include <stdio.h>

typedef void *FreeList;

extern FreeList freelistcreate(size_t size, int l, int u);
extern void     freelistdelete(FreeList f, int l, int u);

// f: base: beginning of pool(0), e: exponent, l: lower
extern void *freelistalloc(FreeList f, void *base, int e, int l);
// f: base: beginning of pool(0), mem: data addr to clear, e: exponent, l: lower
extern void  freelistfree(FreeList f, void *base, void *mem, int e, int l);

extern int freelistsize(FreeList f, void *base, void *mem, int l, int u);
extern void freelistprint(FreeList f, int l, int u);

#endif
