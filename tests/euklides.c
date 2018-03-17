#include <stdio.h>

int main(void) {
    int a;
    int b;
    scanf("%d", &a);
    scanf("%d", &b);
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    printf("%d", a);
    putchar('\n');
    return 0;
}
