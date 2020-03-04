global main
main: 
mov a, dword [EBP  - 4]
mov 2, byte 2
mov [EBP  - 0], 2
mov b, dword [EBP  - 4]
mov 3, byte 3
mov [EBP  - 0], 3
mov a, dword [EBP  - 4]
mov b, dword [EBP  - 4]
add a, b
mov c, dword [EBP  - 4]
mov [EBP  - 0], a
mov a, dword [EBP  - 4]
ret 
