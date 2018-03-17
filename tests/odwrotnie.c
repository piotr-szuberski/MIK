#include <stdio.h>

int main(void) {
    int a[10];
    int i = 0;
    while (i < 10) {
        scanf("%d", &a[i]);
        ++i;
    }
    i = 9;
    while (i != -1) {
        printf("%d", a[i]);
        putchar('\n');
        --i;
    }
    return 0;
}
