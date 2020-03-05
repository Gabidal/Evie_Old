global main
main: 
mov EAX , dword [EBP  + 12]
mov EBX , dword [EBP  + 16]
imul EAX , EBX 
mov [EBP  - 4], EAX 
mov EAX , dword [EBP  - 4]
ret 
