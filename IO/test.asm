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
push dword [ebp  - 8]
push dword [ebp  - 4]
call _square
mov [ebp  - 12], eax 
mov eax , dword [ebp  - 12]
leave 
ret
 
_square: 
push ebp 
mov ebp , esp 
mov ecx , dword [ebp  + 8]
movss xmm0 ,  [ebp  + 28]
cvttss2si ecx , xmm0 
imul ecx , ecx 
mov [ebp  - 4], ecx 
mov eax , dword [ebp  - 4]
leave 
ret
 
