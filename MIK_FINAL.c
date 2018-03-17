/*Piotr Szuberski, Zadanie nr 2 - MIK
  mail kontaktowy: p.szuberski@student.uw.edu.pl
  program wczytuje z wejścia dane w zapisie deksarnym
  a następnie sekwencyjnie wykonuje zapisane w nim instrukcje.
  Jest to implementacja interpretera miki.
  */
#include <stdio.h>
#include <stdlib.h>

#define CORE_DUMP 0
#define GET_INT 1
#define PUT_INT 2
#define GET_CHAR 3
#define PUT_CHAR 4
#define PUT_STRING 5

#define REJESTRY 16
#define LIMIT 256

#define DZ 10
#define BIN 2
#define US 8
#define SZ 16

#define CYFRY 48
#define AP 65
#define QX 81
#define YZ 89

/*pomocnicza funkcja do wypisania - nie wstawia znaku '\n'
  żeby po ostatnim '%' nie było entera (poprawne dane są zakończone
  tym znakiem)*/
void wypisz_core_dump(int TAB[], int limit, int start) {
    int i;
    for (i = start; i < limit; i++)
        fprintf(stderr, "%d ", TAB[i]);
    fprintf(stderr, "\n");
    fputc('%', stderr);
}

/*funkcja wypisująca aktualny zapis stanu maszyny na wyjście diagnostyczne*/
void core_dump(int reg[], int mem[], int instr[], int a) {
    int r = REJESTRY;
    int m = LIMIT;

    wypisz_core_dump(reg, r, 0);
    fprintf(stderr, "\n");
    wypisz_core_dump(mem, m, 0);
    fprintf(stderr, "\n");
    wypisz_core_dump(instr, reg[a], 0);
    fprintf(stderr, "\n");
    wypisz_core_dump(instr, m, reg[a]);
}

/*pomocnicza funkcja określająca, jaką wartość ma wczytany właśnie znak
  w systemie deksarnym*/
void jaka_liczba(int *x) {
    if (*x >= 'A' && *x <= 'P')
        *x = *x - AP;
    if (*x >= '0' && *x <= '9')
        *x = *x - CYFRY;
    if (*x >= 'Q' && *x <= 'X')
        *x = *x - QX;
    if (*x == 'Y')
        *x = 1;
    if (*x == 'Z')
        *x = 0;
}

/*pomocnicza funkcja zwiększająca 'a' względem wczytanego właśnie 'b'*/
void mnoznik(int b, int *a) {
    if (b >= 'A' && b <= 'P')
        *a *= SZ;
    if (b >= '0' && b <= '9')
        *a *= DZ;
    if (b >= 'Q' && b <= 'X')
        *a *= US;
    if (b == 'Y' || b == 'Z')
        *a *= BIN;
}

/*funkcja wczytująca dane wejściowe i zapisująca je do odpowiedniej tablicy
  Przy poprawnych danych gdy i = n musi być a = '%'
  zmienna a - wczytuje pierwszy znak
  zmienna b - wczytuje kolejne znaki i określa, przez jaki mnożnik należy
              pomnożyć a
  zmienna m - początek tablicy
  zmienna n - koniec tablicy
  gdy a lub b = '%', program kończy się i uzupełnia resztę tablicy zerami
  funkcja oddaje wartość i albo i+1 dla określenia licznika rozkazów w 
  instrukcjach oraz n w przypadku gdy licznik rozkazów ma wynosić 0*/
int pobranie_danych(int A[], int n, int m) {
    int i, j, a, b;
    for (i = m; i <= n; i++) {
        do {
            a = getchar();
            if (a == '%') {
                for (j = i; j < n; j++)
                    A[j] = 0;
                return i;
            }
        } while ((a == ' ') || (a == '\n'));
        jaka_liczba(&a);
        b = getchar();
        if (b == '%') {
            A[i] = a;
            for (j = i + 1; j < n; j++)
                A[j] = 0;
            return i + 1;
        }
        while ((b != ' ') && (b != '\n')) {
            mnoznik(b, &a);
            jaka_liczba(&b);
            a += b;
            b = getchar();
            if (b == '%') {
                A[i] = a;
                for (j = i + 1; j < n; j++)
                    A[j] = 0;
                return i + 1;
            }
        }
        A[i] = a;
    }
    return n;
}

/*określenie i zapisanie wartości op, a, b, c na podstawie wartości
  instrukcji którą wskazuje licznik rozkazów*/
void odczyt_instrukcji(int instr[], int pc, int *c, int *b, int *a, int *op) {
    int pom = instr[pc];
    *op = pom >> 12;
    *a = (pom >> 8) & 15;
    *b = (pom >> 4) & 15;
    *c = pom & 15;
}

/*funkcja nr 0.1*/
void divide(int reg[], int a, int b, int c) {
    int trc, trb;
    trc = reg[c];
    if (trc != 0) {
        trb = reg[b];
        reg[a] = trb / trc;
        reg[(a + 1) % REJESTRY] = trb % trc;
    }
}

/*funkcja nr 1.1*/
void return1(int *pc, int mem[], int reg[], int a, int b, int c) {
    int tpc = *pc;
    *pc = mem[reg[a]];
    reg[a] = (reg[a] + reg[c] + 1) % LIMIT;
    reg[b] = tpc;
}

/*funkcja nr 2.1*/
void compare(int reg[], int a, int b, int c) {
    reg[a] = (reg[b] < reg[c]) ? 1 : 0;
}

/*funkcja nr 3.1*/
void subtract(int reg[], int a, int b, int c) {
    int tma;
    tma = (reg[b] - reg[c]) % LIMIT;
    reg[a] = (tma < 0) ? tma + LIMIT : tma;
}

/*funkcja nr 4.1*/
void load_indexed(int reg[], int mem[], int a, int b, int c) {
    reg[a] = mem[(reg[b] + reg[c]) % LIMIT];
}

/*funkcja nr 5.1*/
void store_indexed(int mem[], int reg[], int a, int b, int c) {
    mem[(reg[b] + reg[c]) % LIMIT] = reg[a];
}

/*funkcja nr 6.1*/
void multiply(int reg[], int a, int b, int c) {
    int x;
    x = reg[b] * reg[c];
    reg[(a + 1) % REJESTRY] = x / LIMIT;
    reg[a] = x % LIMIT;
}

/*funkcja nr 7.1*/
void call_indexed(int *pc, int mem[], int reg[], int a, int b, int c) {
    int tpc = *pc;
    *pc = mem[(reg[b] + reg[c]) % LIMIT];
    reg[a] = tpc;
}

/*funkcja nr 8*/
void jump_if_zero(int reg[], int a, int b, int c, int *pc) {
    int bc;
    bc = (b * SZ + c) % LIMIT;
    if (reg[a] == 0)
        *pc = bc;
}

/*funkcja nr 9*/
void jump_if_not_zero(int reg[], int a, int b, int c, int *pc) {
    int bc;
    bc = (b * SZ + c) % LIMIT;
    if (reg[a] != 0)
        *pc = bc;
}

/*funkcja nr 10*/
void call_subroutine(int reg[], int a, int b, int c, int *pc) {
    int bc;
    bc = (b * SZ + c) % LIMIT;
    reg[a] = *pc;
    *pc = bc;
}

/*funkcja nr 11*/
void call(int mem[], int reg[], int a, int b, int c, int *pc) {
    int bc, x;
    bc = (b * SZ + c) % LIMIT;
    x = reg[a] - 1;
    if (x < 0)
        x += LIMIT;
    reg[a] = x;
    mem[reg[a]] = *pc;
    *pc = bc;
}

/*funkcja nr 12*/
void load_register(int reg[], int mem[], int a, int b, int c) {
    int bc;
    bc = (b * SZ + c) % LIMIT;
    reg[a] = mem[bc];
}

/*funkcja nr 13*/
void store_register(int mem[], int reg[], int a, int b, int c) {
    int bc;
    bc = (b * SZ + c) % LIMIT;
    mem[bc] = reg[a];
}

/*funkcja nr 14*/
void load_constant(int reg[], int a, int b, int c) {
    int bc;
    bc = (b * SZ + c) % LIMIT;
    reg[a] = bc;
}

/*funkcja nr 15
  zmienna tra - pobiera i dopasowuje wczytaną liczbę
  wyraz[] - na nią zapisywane są wartości z mem[] jako char
  znak - przyjmuje wartość char z reg[x] do putchar */
void system_call(int reg[], int mem[], int instr[], int a, int b, int c) {
    int bc, tra;
    char znak;
    char wyraz[LIMIT];
    int i;

    bc = (b * SZ + c) % LIMIT;
    switch (bc) {
        case CORE_DUMP:
            core_dump(reg, mem, instr, a);
            break;
        case GET_INT:
            if (scanf("%d", &tra) != 1)
                reg[(a + 1) % LIMIT] = 0;
            else {
                tra = tra % LIMIT;
                if (tra < 0)
                    tra += LIMIT;
                reg[(a + 1) % LIMIT] = 1;
                reg[a] = tra;
            }
            break;
        case PUT_INT:
            printf("%d", reg[a]);
            break;
        case GET_CHAR:
            tra = getchar();
            if (tra == EOF)
                reg[(a + 1) % LIMIT] = 0;
            else {
                reg[(a + 1) % LIMIT] = 1;
                reg[a] = tra;
            }
            break;
        case PUT_CHAR:
            znak = (char) reg[a];
            printf("%c", znak);
            break;
        case PUT_STRING:
            for (i = 0; i < LIMIT; i++) {
                wyraz[i] = (char) mem[i];
            }
            printf("%s", &wyraz[reg[a]]);
            break;
        default:
            break;
    }
}

/*funkcja nr 0.2*/
void push(int reg[], int mem[], int a, int b) {
    int x;
    x = reg[a] - 1;
    if (x < 0)
        x += LIMIT;
    reg[a] = x;
    mem[reg[a]] = reg[b];

}

/*funkcja nr 1.2*/
void pop(int reg[], int mem[], int a, int b) {
    int x;
    x = (reg[a] + 1) % LIMIT;
    reg[b] = mem[reg[a]];
    reg[a] = x;
}

/*funkcja nr 2.2*/
void shift_left(int reg[], int a, int b) {
    reg[a] = (reg[b] << 1) % LIMIT;
}

/*funkcja nr 3.2*/
void shift_right(int reg[], int a, int b) {
    reg[a] = (reg[b] >> 1) % LIMIT;
}

/*funkcja nr 4.2*/
void add(int reg[], int a, int b, int c) {
    reg[a] = (reg[b] + reg[c]) % LIMIT;
}

/*funkcja nr 5.2*/
void bitwise_or(int reg[], int a, int b, int c) {
    reg[a] = reg[b] | reg[c];
}

/*funkcja nr 6.2*/
void bitwise_and(int reg[], int a, int b, int c) {
    reg[a] = reg[b] & reg[c];
}

/*funkcja nr 7.2*/
void bitwise_exclusive_or(int reg[], int a, int b, int c) {
    reg[a] = reg[b] ^ reg[c];
}

/*funkcja nr 0.3*/
void halt(int reg[], int a) {
    exit(reg[a]);
}

/*funkcja nr 1.3*/
void return_from_subroutine(int reg[], int a, int c, int *pc) {
    int tpc;
    tpc = *pc;
    *pc = reg[c];
    reg[a] = tpc;
}

int main(void) {
    int reg[REJESTRY];
    int mem[LIMIT];
    int instrukcje[LIMIT];
    int pc, a, b, c, op, pc_zero;
    int limit = LIMIT;
    int rejestry = REJESTRY;

    pobranie_danych(reg, rejestry, 0);
    pobranie_danych(mem, limit, 0);
    pc_zero = pobranie_danych(instrukcje, limit, 0);
    if (pc_zero < limit) {
        pobranie_danych(instrukcje, limit, pc_zero);
        pc = pc_zero;
    } else {
        pc = 0;
    }
    while (pc < LIMIT) {
        odczyt_instrukcji(instrukcje, pc, &c, &b, &a, &op);
        pc = (pc + 1) % LIMIT;
        switch (op) {
            case 0:
                if (b != c)
                    divide(reg, a, b, c);
                if ((a != b) && (b == c))
                    push(reg, mem, a, b);
                if ((a == b) && (b == c))
                    halt(reg, a);
                break;
            case 1:
                if ((a != b) && (a != c))
                    return1(&pc, mem, reg, a, b, c);
                if ((a != b) && (a == c))
                    pop(reg, mem, a, b);
                if (a == b)
                    return_from_subroutine(reg, a, c, &pc);
                break;
            case 2:
                if (b != c)
                    compare(reg, a, b, c);
                if (b == c)
                    shift_left(reg, a, b);
                break;
            case 3:
                if (b != c)
                    subtract(reg, a, b, c);
                if (b == c)
                    shift_right(reg, a, b);
                break;
            case 4:
                if (b <= c)
                    load_indexed(reg, mem, a, b, c);
                if (b > c)
                    add(reg, a, b, c);
                break;
            case 5:
                if (c >= b)
                    store_indexed(mem, reg, a, b, c);
                if (b > c)
                    bitwise_or(reg, a, b, c);
                break;
            case 6:
                if (b <= c)
                    multiply(reg, a, b, c);
                if (b > c)
                    bitwise_and(reg, a, b, c);
                break;
            case 7:
                if (b <= c)
                    call_indexed(&pc, mem, reg, a, b, c);
                if (b > c)
                    bitwise_exclusive_or(reg, a, b, c);
                break;
            case 8:
                jump_if_zero(reg, a, b, c, &pc);
                break;
            case 9:
                jump_if_not_zero(reg, a, b, c, &pc);
                break;
            case 10:
                call_subroutine(reg, a, b, c, &pc);
                break;
            case 11:
                call(mem, reg, a, b, c, &pc);
                break;
            case 12:
                load_register(reg, mem, a, b, c);
                break;
            case 13:
                store_register(mem, reg, a, b, c);
                break;
            case 14:
                load_constant(reg, a, b, c);
                break;
            case 15:
                system_call(reg, mem, instrukcje, a, b, c);
                break;
            default:
                break;
        }
    }
    return 0;
}