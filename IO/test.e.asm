.intel_syntax noprefix
.global main
banana:
mov dword ptr [rcx + 0 ], dword ptr 1
mov dword ptr [rcx + 4 ], dword ptr 2
mov dword ptr [rcx + 8 ], dword ptr 3
mov rax, rcx
ret 
ret 


set:
mov r8d, dword ptr [rdx + 0 ]
mov dword ptr [rcx + 0 ], r8d
mov r8d, dword ptr [rdx + 4 ]
mov dword ptr [rcx + 4 ], r8d
mov edx, dword ptr [rdx + 8 ]
mov dword ptr [rcx + 8 ], edx
mov rax, rcx
ret 
ret 


main:
push rbx
sub rsp, dword ptr 24
lea rbx, qword ptr [rsp ]
mov rdx, rbx
call banana
lea r8, qword ptr [rsp + 12 ]
mov rcx, r8
lea rbx, qword ptr [rsp ]
mov rdx, rbx
call set
lea rbx, qword ptr [rsp ]
mov rax, rbx
add rsp, dword ptr 24
pop rbx
ret 
add rsp, dword ptr 24
pop rbx
ret 


