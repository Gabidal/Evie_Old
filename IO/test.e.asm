.intel_syntax noprefix
.global main
banana:
mov dword ptr [rcx + 0 ], 1
mov dword ptr [rcx + 4 ], 2
mov dword ptr [rcx + 8 ], 3
mov rax, rcx
ret 
ret 


main:
sub rsp, 24
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call banana
mov rcx, rax
call banana
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call banana
mov rcx, rax
call banana
mov ecx, dword ptr [rax + 4 ]
mov dword ptr [rax + 0 ], ecx
if0:
mov ecx, dword ptr [rsp + 0 ]
cmp ecx, 1
jne else1
mov ecx, dword ptr [rsp + 0 ]
mov dword ptr [rsp + 4 ], ecx
jmp else2_END
if0_END:
else1:
mov ecx, dword ptr [rsp + 0 ]
mov edx, dword ptr [rsp + 4 ]
cmp ecx, edx
jne else2
mov ecx, dword ptr [rsp + 8 ]
mov dword ptr [rsp + 4 ], ecx
jmp else2_END
else1_END:
else2:
mov ecx, dword ptr [rsp + 4 ]
mov edx, dword ptr [rsp + 8 ]
cmp ecx, edx
jne else2_END
mov ecx, dword ptr [rsp + 0 ]
mov dword ptr [rsp + 8 ], ecx
else2_END:
mov ecx, 12
call _Z8allocatei
mov rcx, rax
call banana
mov rax, rax
add rsp, 24
ret 
add rsp, 24
ret 


