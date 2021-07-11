.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text
_Z4mainv:
push rsi
push rdi
push rbx
sub rsp, 32
mov ecx, 8
call _V17internal_allocatex_rPh
mov rcx, rax
add qword ptr [rcx + 8 ], 1
mov rbx, rcx
jmp Return_Here_41
Return_Here_41:
mov rcx, rbx
add qword ptr [rcx + 8 ], 1
mov rdi, rcx
mov rdi, rbx
mov dword ptr [rdi + 0 ], 1
mov dword ptr [rdi + 4 ], 2
mov rcx, rdi
add qword ptr [rcx + 8 ], 1
mov rsi, rcx
mov rsi, rdi
jmp Return_Here_42
Return_Here_42:
mov rcx, qword ptr [rsi + 0 ]
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsi + 8 ]
mov qword ptr [rsp + 8 ], rcx
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov r8d, dword ptr [rcx + 0 ]
mov r8d, r8d
mov rcx, rcx
call _ZN3foo10DestructorEP3foo
mov rcx, rbx
call _ZN3foo10DestructorEP3foo
mov rcx, rsi
call _ZN3foo10DestructorEP3foo
mov rcx, rdi
call _ZN3foo10DestructorEP3foo
jmp Return_Here_40
Return_Here_40:
mov eax, 1
add rsp, 32
pop rbx
pop rdi
pop rsi
ret 
add rsp, 32
pop rbx
pop rdi
pop rsi
ret 


_Z10Start_Testv:
push rbp
push rsi
push rdi
push rbx
sub rsp, 32
mov ecx, 8
call _V17internal_allocatex_rPh
mov rcx, rax
add qword ptr [rcx + 8 ], 1
mov rbx, rcx
jmp Return_Here_38
Return_Here_38:
mov rcx, rbx
add qword ptr [rcx + 8 ], 1
mov rdi, rcx
mov rdi, rbx
mov dword ptr [rdi + 0 ], 1
mov dword ptr [rdi + 4 ], 2
mov rcx, rdi
add qword ptr [rcx + 8 ], 1
mov rsi, rcx
mov rsi, rdi
jmp Return_Here_39
Return_Here_39:
mov rcx, qword ptr [rsi + 0 ]
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsi + 8 ]
mov qword ptr [rsp + 8 ], rcx
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov r8d, dword ptr [rcx + 0 ]
mov ebp, r8d
mov rcx, rcx
call _ZN3foo10DestructorEP3foo
mov rcx, rbx
call _ZN3foo10DestructorEP3foo
mov rcx, rsi
call _ZN3foo10DestructorEP3foo
mov rcx, rdi
call _ZN3foo10DestructorEP3foo
mov eax, ebp
add rsp, 32
pop rbx
pop rdi
pop rsi
pop rbp
ret 
add rsp, 32
pop rbx
pop rdi
pop rsi
pop rbp
ret 


_ZN3foo10DestructorEP3foo:
push rbx
if_19:
cmp rcx, 0
je if_19_END
mov r8, qword ptr [rcx + 8 ]
sub r8, 1
cmp r8, 1
jge if_19_END
mov r8, rcx
add qword ptr [r8 + 8 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_37:
mov rcx, rbx
call _ZN3foo10DestructorEP3foo
if_19_END:
pop rbx
ret 


.section .data
