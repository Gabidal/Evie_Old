global main
main: 
push ebp 
mov ebp , esp 
push byte 1
push byte 2
call _square
mov [ebp  - 4], eax 
mov eax , dword [ebp  - 4]
leave 
ret
 
_square: 
push ebp 
mov ebp , esp 
mov eax , dword [ebp  + 12]
mov ebx , dword [ebp  + 16]
imul eax , ebx 
mov [ebp  - 4], eax 
mov eax , dword [ebp  - 4]
leave 
ret
 
