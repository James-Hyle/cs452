// use: gcc main.c balloc.c utils.c -o main
#include "balloc.h"
#include "utils.h"

int main() {
    // Balloc b = bcreate(32,5,5);
    // bprint(b);

    // printf("b: %p\n", b);
    // printf("b: %p\n", (void*) &b);

    //utils testing 
    size_t bmt = 0xFF;
    // TEST BITCLEAR
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
}
