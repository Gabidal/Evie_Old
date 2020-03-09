global main
main: 
push ebp 
mov ebp , esp 
mov eax , dword 1.0
cvtsi2sd xmm0 , eax 
movss xmm0 , xmm0 
movss [ebp  - 4], xmm0 
movss xmm0 ,  [ebp  - 4]
cvttss2si ebx , xmm0 
mov ebx , ebx 
mov [ebp  - 16], ebx 
movss xmm0 ,  [ebp  - 4]
mov ebx , dword [ebp  - 16]
cvtsi2sd xmm0 , ebx 
mulss xmm0 , xmm0 
movss [ebp  - 4], xmm0 
movss xmm0 ,  [ebp  - 4]
leave 
ret
 
