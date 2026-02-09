#include "freelist.h"

FreeList freelistcreate(size_t size, int l, int u) {
  
  FreeL l = mmalloc(size);
  for (int i = l; i <= u; i++) {

  }
}

void freelistdelete(FreeList f, int l, int u) {
  if (f==NULL) return;
  mmfree(f, sizeof(f));
}

// f: base: beginning of pool(0), e: exponent, l: lower
void *freelistalloc(FreeList f, void *base, int e, int l) {

}

// f: base: beginning of pool(0), mem: data addr to clear, e: exponent, l: lower
void freelistfree(FreeList f, void *base, void *mem, int e, int l) {
  
}

int freelistsize(FreeList f, void *base, void *mem, int l, int u) {

}

void freelistprint(FreeList f, int l, int u) {

}
