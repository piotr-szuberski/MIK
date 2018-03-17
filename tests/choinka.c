#include <stdio.h>

void spacje(int n) {
    int i;
    for (i = 0; i < n; ++i) {
        putchar(' ');
    }
}

int main(void) {
    int wysokosc, i, j;
    scanf("%d", &wysokosc);
    for (i = 0; i < wysokosc; ++i) {
        spacje(wysokosc - 1 - i);
        putchar('*');
        for (j = 0; j < 2 * i; ++j) {
            putchar('*');
        }
        putchar('\n');
    }
    for (i = 0; i < 3; ++i) {
        spacje(wysokosc - 2);
        printf("***\n");
    }
    return 0;
}
