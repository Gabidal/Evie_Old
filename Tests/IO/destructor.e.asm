.intel_syntax noprefix
.global Start_Test
.global main
.section .text
main:
mov eax, 1
ret 
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
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
jmp Return_Here_5
Return_Here_5:
mov rcx, rbx
add qword ptr [rcx + 0 ], 1
mov rdi, rcx
mov rdi, rbx
mov dword ptr [rdi + 0 ], 1
mov dword ptr [rdi + 4 ], 2
mov rcx, rdi
add qword ptr [rcx + 0 ], 1
mov rsi, rcx
mov rsi, rdi
jmp Return_Here_9
Return_Here_9:
mov rcx, qword ptr [rsi + 0 ]
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsi + 8 ]
mov qword ptr [rsp + 8 ], rcx
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov r8d, dword ptr [rcx + 12 ]
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
mov r8, qword ptr [rcx + 0 ]
sub r8, 1
cmp r8, 1
jge if_0_END
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_1:
mov rcx, rbx
call Destructor
if_0_END:
pop rbx
ret 


.section .data
