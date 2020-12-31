.intel_syntax noprefix
.global apple
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
lea rdx, qword ptr [rsp ]
mov rcx, rdx
call banana
mov rax, rax
add rsp, 24
ret 
add rsp, 24
ret 


apple:
push rdi
push rbx
mov rbx, rcx
call banana
mov eax, dword ptr [rdi + 0 ]
pop rdi
pop rbx
ret 
pop rdi
pop rbx
ret 


