#define _get_int 1
#define _put_int 2
#define _put_char 4

    0
\_r0
    "\n"
\_ra
    0
    0
\_rb
    0
    0
%
%
%
    sys _ra _get_int
    sys _rb _get_int
\[
    sub G _ra _rb
    jze G (
    cmp G _rb _ra
    jze G [
    sub _ra _ra _rb
    jze A (
\]
    sub _rb _rb _ra
\)
    jze A ]
\)
    sys _ra _put_int
    sys _r0 _put_char
    hlt A
%
