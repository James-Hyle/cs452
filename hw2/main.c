#include "balloc.c"

int main() {
    Balloc b = bcreate(32,32,32);
    fprintf("b: ", b);
}
