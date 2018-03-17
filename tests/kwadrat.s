#define _get_int 1
#define _put_int 2
#define _put_char 4

    0
\_r0
    "\n"
%
%
%
    sys C _get_int
    mul C C C
    sys C _put_int
    sys _r0 _put_char
    hlt A
%
