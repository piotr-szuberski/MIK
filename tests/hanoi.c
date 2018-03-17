#include <stdio.h>

void h(int n, int a, int b, int p) {
    if (n > 0) {
        h(n - 1, a, p, b);
        printf("%d", a);
        printf("->");
        printf("%d", b);
        putchar('\n');
        h(n - 1, p, b, a);
    }
}

int main(void) {
    h(4, 1, 3, 2);
    return 0;
}
