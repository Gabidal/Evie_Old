global main
main: 
push ebp 
mov ebp , esp 
mov al , byte 1
movsx eax , al 
mov eax , eax 
mov [ebp  - 4], eax 
mov eax , dword [ebp  - 4]
mov [ebp  - 8], eax 
mov eax , dword [ebp  - 4]
mov ebx , dword [ebp  - 8]
imul eax , ebx 
mov [ebp  - 4], eax 
mov eax , dword [ebp  - 4]
leave 
ret
 
