#include <stdio.h>

int main(void) {
    int x;
    int s = 0;
    for (;;) {
        if (scanf("%d", &x) != 1) {
            break;
        }
        if (x == 0) {
            break;
        }
        s += x;
    }
    printf("%d", s);
    putchar('\n');
    return 0;
}
