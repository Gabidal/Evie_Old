main:
mov ecx, dword 1
mov edx, dword 2
mov r8d, dword 3
mov r9d, dword 4
push dword 6
push dword 5
call apple
add rsp, dword 8
mov ecx, eax
mov eax, ecx
ret 
ret 


apple:
add ecx, edx
add ecx, r8d
add ecx, r9d
mov edx, dword [(rsp + 8) ]
add ecx, edx
mov edx, dword [(rsp + 12) ]
add ecx, edx
mov eax, ecx
ret 
ret 


