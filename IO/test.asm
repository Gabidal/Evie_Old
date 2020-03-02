global main
main: 
; The Right Side in = has already initialized.
mov [EBP  - 4], byte 2
_while4: 
mov EAX , dword [EBP  - 4]

cmp EAX , EAX 
jnl _while4END
mov EBX , EAX 

add EBX , EBX 
; The Left Side in + has already initialized.
add EBX , EBX 
; The Right Side in = has already initialized.
mov [EBP  - 4], EBX 
jmp _while4
_while4END: 
mov EAX , EBX 

ret 
