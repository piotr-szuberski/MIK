#include <stdio.h>

#define N 4

int main(void) {
    int a[N] = {0};
    int *b = a + N;
    int *p;
start:
    p = b;
    while (p != a) {
        --p;
        printf("%d", *p);
    }
    putchar('\n');
    for (p = a; p != b && *p != 0; ++p) {
        *p = 0;
    }
    if (p != b) {
        *p = 1;
    }
    core_dump(start);
    return 0;
}
