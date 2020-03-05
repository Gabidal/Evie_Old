global main
main: 
push dword [EBP  + 12]
push dword [EBP  + 16]
call _square
mov [EBP  - 4], EAX 
mov EAX , dword [EBP  - 4]
ret 
_square: 
mov EAX , dword [EBP  + 12]
mov EBX , dword [EBP  + 16]
imul EAX , EBX 
mov [EBP  - 4], EAX 
mov EAX , dword [EBP  - 4]
ret 
