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
mov rcx, rcx
mov dword ptr [rcx + 0 ], 1
mov dword ptr [rcx + 4 ], 0
jmp Return_Here_13
Return_Here_13:
mov ecx, 5
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
mov dword ptr [rbx + 0 ], ecx
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rdi, rax
mov ecx, dword ptr [rbx + 4 ]
mov esi, ecx
mov rbp, rdi
mov r12, rdi
mov r13d, 0
cmp r13d, esi
jge while_1_END
while_1:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp r13d, esi
jge while_1_END
jmp while_1
while_1_END:
jmp Return_Here_29
Return_Here_29:
if_0_END:
add dword ptr [rbx + 4 ], 1
Return_Here_26:
mov ecx, 2
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
mov dword ptr [rbx + 0 ], ecx
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rdi, rax
mov ecx, dword ptr [rbx + 4 ]
mov esi, ecx
mov rbp, rdi
mov r12, rdi
mov r13d, 0
cmp r13d, esi
jge while_3_END
while_3:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp r13d, esi
jge while_3_END
jmp while_3
while_3_END:
jmp Return_Here_33
Return_Here_33:
if_2_END:
add dword ptr [rbx + 4 ], 1
Return_Here_32:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
sub dword ptr [rcx + 4 ], 1
Return_Here_25:
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
jmp Return_Here_44
if_4_END:
mov r8, qword ptr [r8 + 8 ]
mov ecx, dword ptr [r8 + rcx * 4 ]
mov r9d, ecx
jmp Return_Here_44
Return_Here_44:
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
mov rcx, rcx
mov dword ptr [rcx + 0 ], 1
mov dword ptr [rcx + 4 ], 0
jmp Return_Here_183
Return_Here_183:
mov ecx, 5
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
mov dword ptr [rbx + 0 ], ecx
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rdi, rax
mov ecx, dword ptr [rbx + 4 ]
mov esi, ecx
mov rbp, rdi
mov r12, rdi
mov r13d, 0
cmp r13d, esi
jge while_6_END
while_6:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp r13d, esi
jge while_6_END
jmp while_6
while_6_END:
jmp Return_Here_199
Return_Here_199:
if_5_END:
add dword ptr [rbx + 4 ], 1
Return_Here_196:
mov ecx, 2
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
mov dword ptr [rbx + 0 ], ecx
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rdi, rax
mov ecx, dword ptr [rbx + 4 ]
mov esi, ecx
mov rbp, rdi
mov r12, rdi
mov r13d, 0
cmp r13d, esi
jge while_8_END
while_8:
lea rcx, qword ptr [r12 + r13 * 4 ]
mov r8d, dword ptr [rbp + r13 * 4 ]
mov dword ptr [rcx ], r8d
add r13d, 1
cmp r13d, esi
jge while_8_END
jmp while_8
while_8_END:
jmp Return_Here_203
Return_Here_203:
if_7_END:
add dword ptr [rbx + 4 ], 1
Return_Here_202:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
sub dword ptr [rcx + 4 ], 1
Return_Here_195:
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
jmp Return_Here_214
if_9_END:
mov r8, qword ptr [r8 + 8 ]
mov ecx, dword ptr [r8 + rcx * 4 ]
mov r9d, ecx
jmp Return_Here_214
Return_Here_214:
jmp Return_Here_186
Return_Here_186:
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
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rax, rax
ret 
ret 


.section .data
