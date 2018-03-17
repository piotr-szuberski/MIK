#define _get_int 1
#define _put_char 4
#define _put_string 5

    0
\_rwysokosc
    0
    0
\_r0
    _m0
\_r1
    " "
\_r2
    "*"
\_r3
    "\n"
\_ri
    0
\_rj
    0
\_r4
    1
\_r5
    3
\_r6
    2
\_r_spacje_n
    0
\_r_spacje_i
    0
%
\_m0
    "*"
    "*"
    "*"
    "\n"
    0
%
\spacje
    ldc _r_spacje_i 0
\[
    cmp P _r_spacje_i _r_spacje_n
    jze P (
    sys _r1 _put_char
    add _r_spacje_i _r_spacje_i _r4
    jze A ]
\)
    rts O O
%
    sys _rwysokosc _get_int
    ldc _ri 0
\[
    cmp P _ri _rwysokosc
    jze P (
    sub _r_spacje_n _rwysokosc _r4
    sub _r_spacje_n _r_spacje_n _ri
    cls O spacje
    sys _r2 _put_char
    ldc _rj 0
\[
    shl P _ri
    cmp P _rj P
    jze P (
    sys _r2 _put_char
    add _rj _r4 _rj
    jze A ]
\)
    sys _r3 _put_char
    add _ri _r4 _ri
    jze A ]
\)
    ldc _ri 0
\[
    cmp P _ri _r5
    jze P (
    sub _r_spacje_n _rwysokosc _r6
    cls O spacje
    sys _r0 _put_string
    add _ri _r4 _ri
    jze A ]
\)
    hlt A
%
