// use: gcc main.c balloc.c utils.c -o main
#include "balloc.h"
#include "utils.h"

int main() {
  // utils testing
  size_t bmt = 0xFF;
  printf("bmt before: %lX\n", bmt);
  printf("bmt before: %lu\n", bmt);
  bitclr(&bmt, 7);
  printf("bmt after bitclr: %lX\n", bmt);
  printf("bmt after bitclr: %lu\n\n", bmt);

  bmt = 0xFF;
  printf("bmt before: %lX\n", bmt);
  printf("bmt before: %lu\n", bmt);
  bitclr(&bmt, 1);
  printf("bmt after bitinv: %lX\n", bmt);
  printf("bmt before: %lu\n", bmt);

  int t = 2;
  printf("e2size(t): %ld\n", e2size(t));

  size_t s = 8;
  printf("size2e: %d\n", size2e(s));


  
  printf("\t\tBUDDY TEST\t\t\n");

  Balloc b = bcreate(1024, 4, 10);
  printf("\nInitial State: Pool created (1024 bytes)\n");
  bprint(b);

  printf("\n--- basic allocations (64B, 32B, 32B) ---\n");
  void *p1 = balloc(b, 64);
  void *p2 = balloc(b, 32);
  void *p3 = balloc(b, 32);
  printf("allocated p1 (64B), p2 (32B), p3 (32B)\n");
  bprint(b);

  printf("\n--- large allocations (128B, 256B) ---\n");
  void *p4 = balloc(b, 128);
  void *p5 = balloc(b, 256);
  printf("allocated p4 (128B), p5 (256B)\n");
  bprint(b);

  printf("\n--- free & coalesce ---\n");
  printf("Freeing p3 (32B)...\n");
  bfree(b, p3);

  printf("Freeing p1 (64B)...\n");
  bfree(b, p1);

  printf("Freeing p2 (32B) -> Should merge p2+p3 (64B), then merge with p1 "
         "(128B)\n");
  bfree(b, p2);
  bprint(b);

  printf("\n--- final cleanup ---\n");
  printf("Freeing p4 (128B)...\n");
  bfree(b, p4);

  printf("Freeing p5 (256B)...\n");
  bfree(b, p5);

  printf("\n---final---\n");
  bprint(b);

  bdelete(b);
  printf("buddy allocator deleted.\n");
  return 0;
}
