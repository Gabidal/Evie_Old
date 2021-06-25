.intel_syntax noprefix
.global Start_Test
.global main
.section .text
main:
push rsi
push rdi
push rbx
sub rsp, 16
mov ecx, 8
call _V17internal_allocatex_rPh
mov rcx, rax
add qword ptr [rcx + 8 ], 1
mov rbx, rcx
jmp Return_Here_48
Return_Here_48:
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
jmp Return_Here_52
Return_Here_52:
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
call Destructor
mov rcx, rbx
call Destructor
mov rcx, rsi
call Destructor
mov rcx, rdi
call Destructor
jmp Return_Here_37
Return_Here_37:
mov eax, 1
add rsp, 16
pop rbx
pop rdi
pop rsi
ret 
add rsp, 16
pop rbx
pop rdi
pop rsi
ret 


Start_Test:
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
jmp Return_Here_29
Return_Here_29:
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
jmp Return_Here_33
Return_Here_33:
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
call Destructor
mov rcx, rbx
call Destructor
mov rcx, rsi
call Destructor
mov rcx, rdi
call Destructor
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


Destructor:
push rbx
if_0:
cmp rcx, 0
je if_0_END
mov r8, qword ptr [rcx + 8 ]
sub r8, 1
cmp r8, 1
jge if_0_END
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_25:
mov rcx, rbx
call Destructor
if_0_END:
pop rbx
ret 


.section .data
