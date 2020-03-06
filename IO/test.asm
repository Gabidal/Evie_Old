global main
main: 
mov eax , dword [ebp  + 12]
cvttss2si eax , xmm0 
movss xmm0 , xmm0 
_=[ebp  - 0], eax 
mov eax , dword [ebp  + 12]
mov ebx , ebx 
mov [ebp  - 0], eax 
mov ebx , dword [ebp  - 4]
ret
 
