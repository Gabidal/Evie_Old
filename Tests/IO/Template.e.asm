.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
push r13
push r12
push rbp
push rsi
push rdi
push rbx
sub rsp, 144
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
mov dword ptr [rbx + 0 ], 1
mov dword ptr [rbx + 4 ], 0
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov qword ptr [rbx + 8 ], rax
jmp Return_Here_33
Return_Here_33:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_1:
mov ecx, dword ptr [rbx + 4 ]
mov r8d, dword ptr [rbx + 0 ]
cmp ecx, r8d
jl if_1_END
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [rbx + 0 ], ecx
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rdi, rax
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov esi, ecx
mov rcx, qword ptr [rbx + 8 ]
mov rbp, rcx
mov r12, rdi
cmp esi, 0
jge while_2_END
while_2:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp esi, 0
jge while_2_END
jmp while_2
while_2_END:
jmp Return_Here_44
Return_Here_44:
mov qword ptr [rbx + 8 ], rdi
if_1_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 5
add dword ptr [rbx + 4 ], 1
Return_Here_37:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_3:
mov ecx, dword ptr [rbx + 4 ]
mov r8d, dword ptr [rbx + 0 ]
cmp ecx, r8d
jl if_3_END
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [rbx + 0 ], ecx
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rdi, rax
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov esi, ecx
mov rcx, qword ptr [rbx + 8 ]
mov rbp, rcx
mov r12, rdi
cmp esi, 0
jge while_4_END
while_4:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp esi, 0
jge while_4_END
jmp while_4
while_4_END:
jmp Return_Here_46
Return_Here_46:
mov qword ptr [rbx + 8 ], rdi
if_3_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 2
add dword ptr [rbx + 4 ], 1
Return_Here_41:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
sub dword ptr [rcx + 4 ], 1
Return_Here_45:
mov ecx, 0
lea r8, qword ptr [rsp ]
mov r8, r8
add qword ptr [r8 + 0 ], 1
mov r8, r8
if_5:
mov r9d, dword ptr [r8 + 4 ]
cmp ecx, r9d
jle if_5_END
mov r9d, 0
jmp Return_Here_49
if_5_END:
mov r8, qword ptr [r8 + 8 ]
mov ecx, dword ptr [r8 + rcx * 4 ]
mov r9d, ecx
jmp Return_Here_49
Return_Here_49:
mov eax, r9d
add rsp, 144
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
ret 
add rsp, 144
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
ret 


main:
push r13
push r12
push rbp
push rsi
push rdi
push rbx
sub rsp, 24
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
mov dword ptr [rbx + 0 ], 1
mov dword ptr [rbx + 4 ], 0
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov qword ptr [rbx + 8 ], rax
jmp Return_Here_60
Return_Here_60:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_6:
mov ecx, dword ptr [rbx + 4 ]
mov r8d, dword ptr [rbx + 0 ]
cmp ecx, r8d
jl if_6_END
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [rbx + 0 ], ecx
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rdi, rax
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov esi, ecx
mov rcx, qword ptr [rbx + 8 ]
mov rbp, rcx
mov r12, rdi
cmp esi, 0
jge while_7_END
while_7:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp esi, 0
jge while_7_END
jmp while_7
while_7_END:
jmp Return_Here_71
Return_Here_71:
mov qword ptr [rbx + 8 ], rdi
if_6_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 5
add dword ptr [rbx + 4 ], 1
Return_Here_64:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_8:
mov ecx, dword ptr [rbx + 4 ]
mov r8d, dword ptr [rbx + 0 ]
cmp ecx, r8d
jl if_8_END
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [rbx + 0 ], ecx
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rdi, rax
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov esi, ecx
mov rcx, qword ptr [rbx + 8 ]
mov rbp, rcx
mov r12, rdi
cmp esi, 0
jge while_9_END
while_9:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp esi, 0
jge while_9_END
jmp while_9
while_9_END:
jmp Return_Here_73
Return_Here_73:
mov qword ptr [rbx + 8 ], rdi
if_8_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 2
add dword ptr [rbx + 4 ], 1
Return_Here_68:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
sub dword ptr [rcx + 4 ], 1
Return_Here_72:
mov ecx, 0
lea r8, qword ptr [rsp ]
mov r8, r8
add qword ptr [r8 + 0 ], 1
mov r8, r8
if_10:
mov r9d, dword ptr [r8 + 4 ]
cmp ecx, r9d
jle if_10_END
mov r9d, 0
jmp Return_Here_76
if_10_END:
mov r8, qword ptr [r8 + 8 ]
mov ecx, dword ptr [r8 + rcx * 4 ]
mov r9d, ecx
jmp Return_Here_76
Return_Here_76:
jmp Return_Here_53
Return_Here_53:
mov eax, 1
add rsp, 24
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
ret 
add rsp, 24
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
ret 


____Allocate_int_:
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rax, rax
ret 
ret 


.section .data
