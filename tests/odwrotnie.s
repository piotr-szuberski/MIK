#define _get_int 1
#define _put_int 2
#define _put_char 4

    0
\_ri
    0
\_r0
    10
\_r1
    \1
\_r2
    1
\_r3
    "\n"
\_ra
    _ma
%
\_ma
%
%
    ldc _ri 0
\[
    cmp P _ri _r0
    jze P (
    sys N _get_int
    sti N _ri _ra
    add _ri _r2 _ri
    jze A ]
\)
    ldc _ri 9
\[
    sub P _ri _r1
    jze P (
    ldi N _ri _ra
    sys N _put_int
    sys _r3 _put_char
    sub _ri _ri _r2
    jze A ]
\)
    hlt A
%
