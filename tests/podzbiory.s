#define _core_dump 0
#define _put_int 2
#define _put_char 4

#define N 4

    0
\_r0
    N
\_r1
    "\n"
\_r2
    1
\_rstart
    _start
\_ra
    _ma
\_rb
    0
\_rp
    0
%
\_ma
%
%
    add _rb _ra _r0
\_start
    add _rp _rb A
\[
    sub I _rp _ra
    jze I (
    sub _rp _rp _r2
    ldi I A _rp
    sys I _put_int
    jze A ]
\)
    sys _r1 _put_char
    add _rp _ra A
\[
    sub I _rp _rb
    jze I (
    ldi I A _rp
    jze I (
    sti A A _rp
    add _rp _rp _r2
    jze A ]
\)
\)
    sub I _rp _rb
    jze I (
    sti _r2 A _rp
\)
    sys _rstart _core_dump
    hlt A
%
