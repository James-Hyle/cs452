#ifndef FREELIST_H
#define FREELIST_H

#include <stdio.h>

typedef void *FreeList;

// struct 
typedef struct {
    FreeL *next;
} FreeL;

// freelistcreate: return free list(s) of order from lower to upper
// size: size of free list to be created
// l: lower bound of freelist order
// u: upper bound of freelist order
extern FreeList freelistcreate(size_t size, int l, int u);

// freelistdelete: remove free lists in memory
// f: freelist structure
// l: lower bound of freelist order
// u: upper bound of freelist order
extern void freelistdelete(FreeList f, int l, int u);

// *freelistalloc: return pointer to beginning of new freelist(s) memory
// f: freelist structure
// *base: pointer to base of memory structure
// e: order to free in list
// l: lower bound of freelist order
extern void *freelistalloc(FreeList f, void *base, int e, int l);

// freelistfree: free memory block of 
// f: freelist structure
// *base: pointer to base of memory structure
// *mem: pointer to address in memory structure
// e: order to free in list 
// l: lower bound of freelist order
extern void freelistfree(FreeList f, void *base, void *mem, int e, int l);

// freelistsize: return size of freelist structure
// f: freelist structure
// *base: pointer to base of memory structure
// *mem: pointer to address in memory structure
// l: lower bound of freelist order
// u: upper bound of freelist order
extern int freelistsize(FreeList f, void *base, void *mem, int l, int u);

// freelistprint: print freelist
// f: freelist structure
// l: lower bound of freelist order
// u: upper bound of freelist order
extern void freelistprint(FreeList f, int l, int u);

#endif
