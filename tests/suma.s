#define _get_int 1
#define _put_int 2
#define _put_char 4

    0
\_r0
    "\n"
\_rx
    0
\_r_x
    0
\_rs
    0
%
%
%
\[
    sys _rx _get_int
    jze _r_x {
    jze _rx {
    add _rs _rs _rx
    jze A ]
\}
\}
    sys _rs _put_int
    sys _r0 _put_char
    hlt A
%
