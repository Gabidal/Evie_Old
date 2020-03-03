global main
main: 
; The Right Side in = has already initialized.

_while4: 
mov a, dword [EBP  - 4]
cmp a, byte 3
jnl _while4END
mov a, dword [EBP  - 4]
add dword [EBP  - 4], byte 1
; The Left Side in + has already initialized.

; The Right Side in = has already initialized.

jmp _while4
_while4END: 
mov a, dword [EBP  - 4]
ret 
