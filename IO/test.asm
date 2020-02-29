global _main
_int: 
_short: 
_char: 
_long: 
_float: 
_double: 
_static: 
_const: 
_constexpr: 
_main: 
mov AL , byte [EBP  + 9]

add AL , byte [EBP  + 10]
; The Right Side in = has already initialized.
mov [EBP  - 4], AL 
mov EAX , dword [EBP  - 4]

ret 
