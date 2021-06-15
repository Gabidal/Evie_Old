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
jmp Return_Here_25
Return_Here_25:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_0:
mov ecx, dword ptr [rbx + 4 ]
mov r8d, dword ptr [rbx + 0 ]
cmp ecx, r8d
jl if_0_END
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
jge while_1_END
while_1:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp esi, 0
jge while_1_END
jmp while_1
while_1_END:
jmp Return_Here_65
Return_Here_65:
mov qword ptr [rbx + 8 ], rdi
if_0_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 5
add dword ptr [rbx + 4 ], 1
Return_Here_44:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_2:
mov ecx, dword ptr [rbx + 4 ]
mov r8d, dword ptr [rbx + 0 ]
cmp ecx, r8d
jl if_2_END
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
jge while_3_END
while_3:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp esi, 0
jge while_3_END
jmp while_3
while_3_END:
jmp Return_Here_69
Return_Here_69:
mov qword ptr [rbx + 8 ], rdi
if_2_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 2
add dword ptr [rbx + 4 ], 1
Return_Here_50:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
sub dword ptr [rcx + 4 ], 1
Return_Here_37:
mov ecx, 0
lea r8, qword ptr [rsp ]
mov r8, r8
add qword ptr [r8 + 0 ], 1
mov r8, r8
if_4:
mov r9d, dword ptr [r8 + 4 ]
cmp ecx, r9d
jle if_4_END
mov r9d, 0
jmp Return_Here_62
if_4_END:
mov r8, qword ptr [r8 + 8 ]
mov ecx, dword ptr [r8 + rcx * 4 ]
mov r9d, ecx
jmp Return_Here_62
Return_Here_62:
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
jmp Return_Here_255
Return_Here_255:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_5:
mov ecx, dword ptr [rbx + 4 ]
mov r8d, dword ptr [rbx + 0 ]
cmp ecx, r8d
jl if_5_END
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
jge while_6_END
while_6:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp esi, 0
jge while_6_END
jmp while_6
while_6_END:
jmp Return_Here_295
Return_Here_295:
mov qword ptr [rbx + 8 ], rdi
if_5_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 5
add dword ptr [rbx + 4 ], 1
Return_Here_274:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_7:
mov ecx, dword ptr [rbx + 4 ]
mov r8d, dword ptr [rbx + 0 ]
cmp ecx, r8d
jl if_7_END
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
jge while_8_END
while_8:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp esi, 0
jge while_8_END
jmp while_8
while_8_END:
jmp Return_Here_299
Return_Here_299:
mov qword ptr [rbx + 8 ], rdi
if_7_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 2
add dword ptr [rbx + 4 ], 1
Return_Here_280:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
sub dword ptr [rcx + 4 ], 1
Return_Here_267:
mov ecx, 0
lea r8, qword ptr [rsp ]
mov r8, r8
add qword ptr [r8 + 0 ], 1
mov r8, r8
if_9:
mov r9d, dword ptr [r8 + 4 ]
cmp ecx, r9d
jle if_9_END
mov r9d, 0
jmp Return_Here_292
if_9_END:
mov r8, qword ptr [r8 + 8 ]
mov ecx, dword ptr [r8 + rcx * 4 ]
mov r9d, ecx
jmp Return_Here_292
Return_Here_292:
jmp Return_Here_252
Return_Here_252:
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
