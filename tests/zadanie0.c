/**
 * _Iloczyn wielomianów_
 *
 * Rozwiązanie zadania 0 na laboratorium Wstępu do programowania 2016/2017.
 *
 * Czyta dwa wielomiany reprezentowane przez ciągi współczynników jednomianów,
 * uporządkowane w kolejności rosnącego stopnia, każdy poprzedzony długością.
 * Mnoży wczytane wielomiany i wypisuje wynik w postaci czytelnego równania.
 *
 * Ograniczenia:
 *
 * - maksymalny stopień wielomianu określony jest stałą `MAX_STOPIEN`
 *
 * autor: Artur Zaroda <zaroda@mimuw.edu.pl>
 * wersja: 1.0
 * data: 8 listopada 2016
 */

#include <assert.h>
#include <stdio.h>

#define MAX_STOPIEN 10
#define MAX_JEDNOMIANOW ((MAX_STOPIEN) + 1)

/*
 * Czyta wielomian, zapisuje współczynniki w `a` a stopień na `*n`.
 */
void czytaj(int a[], int *n) {
    int i, d;
    int k = -1;
    scanf("%d", &d);
    for (i = 0; i < d; ++i) {
        int x;
        scanf("%d", &x);
        if (x != 0) {
            assert(i <= MAX_STOPIEN);
            ++k;
            while (k < i) {
                a[k++] = 0;
            }
            a[i] = x;
        }
    }
    *n = k;
}

/*
 * Pisze w czytelnej postaci wielomian stopnia `n` o współczynnikach `a`.
 */
void pisz(const int a[], const int n) {
    if (n == -1) {
        printf("%d", 0);
    } else {
        int i;
        for (i = n; i != -1; --i) {
            if (a[i] != 0) {
                if (i < n && a[i] > 0) {
                    putchar('+');
                }
                if (i > 0 && a[i] == -1) {
                    putchar('-');
                } else if (i == 0 || a[i] != 1) {
                    printf("%d", a[i]);
                }
                if (i > 0) {
                    putchar('x');
                    if (i > 1) {
                        putchar('^');
                        printf("%d", i);
                    }
                }
            }
        }
    }
}

/*
 * Mnoży wielomian stopnia `x` o współczynnikach `a` przez wielomian stopnia
 * `y` o współczynnikach `b`. Współczynniki iloczynu zapisuje w `c` a stopień
 * na `*z`.
 */
void mnoz(
        const int a[], const int x,
        const int b[], const int y,
        int c[], int *z) {
    if (x == -1 || y == -1) {
        *z = -1;
    } else {
        int i;
        *z = x + y;
        assert(*z <= MAX_STOPIEN);
        for (i = 0; i <= *z; ++i) {
            c[i] = 0;
        }
        for (i = 0; i <= x; ++i) {
            int j;
            for (j = 0; j <= y; ++j) {
                c[i + j] += a[i] * b[j];
            }
        }
    }
}

/*
 * Czyta dwa wielomiany, mnoży je i wypisuje wynik jako równanie.
 */
int main(void) {
    int a[MAX_JEDNOMIANOW], x;
    int b[MAX_JEDNOMIANOW], y;
    int c[MAX_JEDNOMIANOW], z;
    czytaj(a, &x);
    czytaj(b, &y);
    mnoz(a, x, b, y, c, &z);
    putchar('(');
    pisz(a, x);
    printf(")(");
    pisz(b, y);
    printf(")=");
    pisz(c, z);
    putchar('\n');
    return 0;
}
