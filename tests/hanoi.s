#define _put_int 2
#define _put_char 4
#define _put_string 5

    0
\_r0
    1
\_r1
    2
\_r2
    3
\_r3
    4
\_r4
    5
\_r5
    _m0
\_r6
    "\n"
%
\_m0
    "-"
    ">"
    0
%
\h
    psh P O
    add O P A
    ldi N _r1 O
    cmp N A N
    jze N (
    ldi N _r3 O
    psh P N
    ldi N _r4 O
    psh P N
    ldi N _r2 O
    psh P N
    ldi N _r1 O
    sub N N _r0
    psh P N
    cal P h
    ldi N _r2 O
    sys N _put_int
    sys _r5 _put_string
    ldi N _r3 O
    sys N _put_int
    sys _r6 _put_char
    ldi N _r2 O
    psh P N
    ldi N _r3 O
    psh P N
    ldi N _r4 O
    psh P N
    ldi N _r1 O
    sub N N _r0
    psh P N
    cal P h
\)
    pop P O
    ret P N _r3
%
    psh P _r1
    psh P _r2
    psh P _r0
    psh P _r3
    cal P h
    hlt A
%
