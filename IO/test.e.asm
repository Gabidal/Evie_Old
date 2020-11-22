main:
push rbx
sub rsp, dword 12
mov ecx, dword 1
mov edx, dword 2
mov r8d, dword 3
mov r9d, dword 4
mov dword [rsp + 0 ], dword 5
mov dword [rsp + 4 ], dword 6
call apple
mov ebx, eax
mov ecx, dword 1
mov edx, dword 2
mov r8d, dword 3
mov r9d, dword 4
mov dword [rsp + 0 ], dword 5
mov dword [rsp + 4 ], dword 6
mov dword [rsp + 8 ], dword 7
call banana
mov ecx, eax
mov edx, ebx
mov ebp, ecx
add edx, ebp
mov eax, edx
add rsp, dword 12
pop rbx
ret 
add rsp, dword 12
pop rbx
ret 


banana:
add ecx, edx
add ecx, r8d
add ecx, r9d
mov edx, dword [(rsp + 8) ]
add ecx, edx
mov edx, dword [(rsp + 12) ]
add ecx, edx
mov edx, dword [(rsp + 16) ]
add ecx, edx
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


