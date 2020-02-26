var: 
main: 
mov EAX , dword 1

add EAX , dword 2
mov [EBP  - 4], dword EAX 
mov EAX , dword [EBP  - 4]

ret 
