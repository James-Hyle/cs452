#include "balloc.c"

int main() {
    Balloc b = bcreate(32,5,5);
    bprint(b);

    printf("b: %p\n", b);
    printf("b: %p\n", (void*) &b);
}
