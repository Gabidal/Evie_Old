.intel_syntax noprefix
.global main
apple:
mov dword ptr [rcx + 0 ], 1
mov dword ptr [rcx + 4 ], 2
mov dword ptr [rcx + 8 ], 3
mov rax, rcx
ret 
ret 


banana:
push rbx
mov dword ptr [rcx + 0 ], 1
mov dword ptr [rcx + 4 ], 2
lea rdx, qword ptr [rcx + 8 ]
mov rbx, rcx
mov rcx, rdx
call apple
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


main:
push rdi
push rbx
sub rsp, 32
mov ecx, 32
call _Z8allocatei
mov rcx, rax
call banana
mov rbx, rax
mov rcx, rbx
call banana
mov rcx, rax
call banana
lea rdi, qword ptr [rax + 0 ]
mov rcx, rbx
call banana
mov rcx, rax
call banana
mov ecx, dword ptr [rax + 4 ]
mov dword ptr [rdi ], ecx
if0:
mov ecx, dword ptr [rbx + 0 ]
cmp ecx, 1
jne else1
mov ecx, dword ptr [rbx + 0 ]
mov dword ptr [rbx + 4 ], ecx
jmp else2_END
if0_END:
else1:
mov ecx, dword ptr [rbx + 0 ]
mov edx, dword ptr [rbx + 4 ]
cmp ecx, edx
jne else2
mov ecx, dword ptr [rbx + 8 + 4 ]
mov dword ptr [rbx + 4 ], ecx
jmp else2_END
else1_END:
else2:
mov ecx, dword ptr [rbx + 8 + 0 ]
mov edx, dword ptr [rbx + 8 + 4 ]
cmp ecx, edx
jne else2_END
mov ecx, dword ptr [rbx + 0 ]
mov dword ptr [rbx + 8 + 0 ], ecx
else2_END:
mov rax, rbx
add rsp, 32
pop rdi
pop rbx
ret 
add rsp, 32
pop rdi
pop rbx
ret 


