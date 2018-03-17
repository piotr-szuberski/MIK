#define _get_int 1
#define _put_int 2
#define _put_char 4
#define _put_string 5

#define MAX_STOPIEN 10
#define MAX_JEDNOMIANOW ((MAX_STOPIEN) + 1)

    0
\_r0
    1
\_ra
    _ma
\_rb
    0
\_rc
    0
\_r_czytaj_i
\_r_pisz_i
\_r_mnoz_i
    0
\_r_czytaj_k
\_r_mnoz_j
    0
\_r_czytaj_d
\_r_mnoz_a1
    0
\_r_czytaj_x
\_r_mnoz_a2
    0
%
\_m0
    0
\_m1
    ")"
    "("
    0
\_m2
    ")"
    "="
    0
\_mx
    0
\_my
    0
\_mz
    0
\_ma
%
\czytaj
    ldc _r_czytaj_k \1
    sys N _get_int
    add _r_czytaj_d N A
    ldc _r_czytaj_i 0
\[
    cmp O _r_czytaj_i _r_czytaj_d
    jze O (
    sys N _get_int
    add _r_czytaj_x N A
    jze _r_czytaj_x [
    ldc O MAX_STOPIEN
    cmp O O _r_czytaj_i
    jze O [
    hlt _r0
\]
    add _r_czytaj_k _r_czytaj_k _r0
\[
    cmp O _r_czytaj_k _r_czytaj_i
    jze O (
    sti A _r_czytaj_k J
    add _r_czytaj_k _r_czytaj_k _r0
    jze A ]
\)
    sti _r_czytaj_x _r_czytaj_i J
\]
    add _r_czytaj_i _r_czytaj_i _r0
    jze A ]
\)
    sti _r_czytaj_k A K
    rts P P
\pisz
    ldc O \1
    sub N K O
    jnz N [
    sys A _put_int
    jze A (
\]
    add _r_pisz_i K A
\[
    sub N _r_pisz_i O
    jze N (
    ldi N _r_pisz_i J
    jze N [
    cmp N _r_pisz_i K
    jze N [
    ldi N _r_pisz_i J
    cls H _nieujemna
    jze G [
    ldc N "+"
    sys N _put_char
\]
\]
    cmp N A _r_pisz_i
    jze N (
    ldi N _r_pisz_i J
    sub N N O
    jnz N (
    ldc N "-"
    sys N _put_char
    jze A [
\)
\)
    jze _r_pisz_i (
    ldi N _r_pisz_i J
    sub N N _r0
    jze N [
\)
    ldi N _r_pisz_i J
    cls I _signed_put_int
\]
\]
    cmp N A _r_pisz_i
    jze N [
    ldc N "x"
    sys N _put_char
    cmp N _r0 _r_pisz_i
    jze N [
    ldc N "^"
    sys N _put_char
    sys _r_pisz_i _put_int
\]
\]
\]
    sub _r_pisz_i _r_pisz_i _r0
    jze A ]
\)
\)
    rts P P
\mnoz
    str P _m0
    ldc _r_mnoz_a1 \1
    sub P K _r_mnoz_a1
    jze P [
    sub P M _r_mnoz_a1
    jnz P (
\]
    sti _r_mnoz_a1 A O
    jze A [
\)
    add P M K
    sti P A O
    ldi P A O
    ldc _r_mnoz_a2 MAX_STOPIEN
    cmp P _r_mnoz_a2 P
    jze P (
    hlt _r0
\)
    ldc _r_mnoz_i 0
\[
    ldi P A O
    cmp P P _r_mnoz_i
    jnz P (
    sti A _r_mnoz_i N
    add _r_mnoz_i _r_mnoz_i _r0
    jze A ]
\)
    ldc _r_mnoz_i 0
\[
    cmp P K _r_mnoz_i
    jnz P (
    ldc _r_mnoz_j 0
\[
    cmp P M _r_mnoz_j
    jnz P (
    ldi P _r_mnoz_i J
    ldi _r_mnoz_a1 _r_mnoz_j L
    mul _r_mnoz_a1 _r_mnoz_a1 P
    add P _r_mnoz_i _r_mnoz_j
    ldi _r_mnoz_a2 N P
    add _r_mnoz_a2 _r_mnoz_a2 _r_mnoz_a1
    sti _r_mnoz_a2 N P
    add _r_mnoz_j _r_mnoz_j _r0
    jze A ]
\)
    add _r_mnoz_i _r_mnoz_i _r0
    jze A ]
\)
\]
    ldr P _m0
    rts P P
%
    ldc P MAX_JEDNOMIANOW
    add _rb P _ra
    add _rc P _rb
    add J _ra A
    ldc K _mx
    cls P czytaj
    add J _rb A
    ldc K _my
    cls P czytaj
    add J _ra A
    ldr K _mx
    add L _rb A
    ldr M _my
    add N _rc A
    ldc O _mz
    cls P mnoz
    ldc J "("
    sys J _put_char
    add J _ra A
    ldr K _mx
    cls P pisz
    ldc J _m1
    sys J _put_string
    add J _rb A
    ldr K _my
    cls P pisz
    ldc J _m2
    sys J _put_string
    add J _rc A
    ldr K _mz
    cls P pisz
    ldc J "\n"
    sys J _put_char
    hlt A
\_signed_put_int
    cls H _nieujemna
    jnz G (
    sub N A N
    ldc G "-"
    sys G _put_char
\)
    sys N _put_int
    rts I I
\_nieujemna
    ldc G 128
    cmp G N G
    rts H H
%
