global main
main: 
push ebp 
mov ebp , esp 
mov al , byte 1
movsx eax , al 
mov eax , eax 
mov [ebp  - 4], eax 
mov al , byte 2
movsx ebx , al 
mov ebx , ebx 
mov [ebp  - 8], ebx 
push dword [ebp  - 4]
push dword [ebp  - 8]
call _square
mov [ebp  - 12], eax 
mov eax , dword [ebp  - 12]
leave 
ret
 
_square: 
push ebp 
mov ebp , esp 
mov eax , dword [ebp  + 16]
mov ebx , dword [ebp  + 20]
imul eax , ebx 
mov [ebp  - 4], eax 
mov eax , dword [ebp  - 4]
leave 
ret
 
