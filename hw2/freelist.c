#include "freelist.h"
#include "utils.h"

FreeList freelistcreate(size_t size, int l, int u) {
  int num_levels = u - l + 1;
  void **lists = mmalloc(num_levels * sizeof(void *));
  if (!lists)
    return NULL;

  for (int i = 0; i < num_levels; i++) {
    lists[i] = NULL;
  }

  return lists;
}

void freelistdelete(FreeList f, int l, int u) {
  if (!f)
    return;
  int num_levels = u - l + 1;
  mmfree(f, num_levels * sizeof(void *));
}

void *freelistalloc(FreeList f, void *base, int e, int l) {
  if (!f)
    return NULL;

  void **lists = (void **)f;
  int idx = e - l;

  void *block = lists[idx];
  if (!block)
    return NULL;

  lists[idx] = *(void **)block;

  return block;
}

void freelistfree(FreeList f, void *base, void *mem, int e, int l) {
  if (!f || !mem)
    return;

  void **lists = (void **)f;
  int idx = e - l;

  if (lists[idx] == mem) {
    return;
  }

  *(void **)mem = lists[idx];
  lists[idx] = mem;
}

int freelistsize(FreeList f, void *base, void *mem, int l, int u) {
  if (!f || !mem)
    return 0;

  void **lists = (void **)f;

  for (int e = l; e <= u; e++) {
    int idx = e - l;
    void *current = lists[idx];

    while (current != NULL) {
      if (current == mem) {
        return e2size(e);
      }
      current = *(void **)current;
    }
  }

  return 0; 
}

void freelistprint(FreeList f, int l, int u) {
  if (!f)
    return;

  void **lists = (void **)f;

  printf("Free Lists (orders %d to %d):\n", l, u);
  for (int e = l; e <= u; e++) {
    int index = e - l;
    printf("  Order %d (size %zu): ", e, e2size(e));

    void *current = lists[index];
    if (!current) {
      printf("empty\n");
    } else {
      while (current != NULL) {
        printf("%p -> ", current);
        current = *(void **)current;
      }
      printf("NULL\n");
    }
  }
}
