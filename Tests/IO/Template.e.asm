.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
push r15
push r14
push r13
push r12
push rbp
push rsi
push rdi
push rbx
sub rsp, 184
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov rbx, rcx
mov dword ptr [rbx + 0 ], 1
mov dword ptr [rbx + 4 ], 0
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
mov r8d, ecx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
mov ecx, ecx
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax
jmp Return_Here_5
Return_Here_5:
mov rcx, qword ptr [rsp + 24 ]
mov qword ptr [rbx + 8 ], rcx
jmp Return_Here_4
Return_Here_4:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
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
mov edi, ecx
mov ecx, edi
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, edi
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rsi, rax
jmp Return_Here_7
Return_Here_7:
mov rbp, rsi
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov r12d, ecx
mov rcx, qword ptr [rbx + 8 ]
mov r13, rcx
mov r14, rbp
mov r15d, 0
cmp r15d, r12d
jge while_1_END
while_1:
lea rcx, qword ptr [r14 + r15 * 4 ]
mov r8d, dword ptr [r13 + r15 * 4 ]
mov dword ptr [rcx ], r8d
mov dword ptr [rsp + 0 ], 
mov dword ptr [rsp + 0 ], r15d
add r15d, 1
cmp r15d, r12d
jge while_1_END
jmp while_1
while_1_END:
jmp Return_Here_8
Return_Here_8:
mov qword ptr [rcx + 8 ], rbp
if_0_END:
mov r8, qword ptr [rcx + 8 ]
mov r9d, dword ptr [rcx + 4 ]
lea r8, qword ptr [r8 + r9 * 4 ]
mov dword ptr [r8 ], 5
add dword ptr [rcx + 4 ], 1
Return_Here_6:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov qword ptr [rsp + 0 ], 
mov qword ptr [rsp + 0 ], rcx
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
mov edi, ecx
mov ecx, edi
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, edi
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rsi, rax
jmp Return_Here_10
Return_Here_10:
mov rbp, rsi
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov r12d, ecx
mov rcx, qword ptr [rbx + 8 ]
mov r13, rcx
mov r14, rbp
mov r15d, 0
cmp r15d, r12d
jge while_3_END
while_3:
lea rcx, qword ptr [r14 + r15 * 4 ]
mov r8d, dword ptr [r13 + r15 * 4 ]
mov dword ptr [rcx ], r8d
mov ecx, r15d
add r15d, 1
cmp r15d, r12d
jge while_3_END
jmp while_3
while_3_END:
jmp Return_Here_11
Return_Here_11:
mov qword ptr [rbx + 8 ], rbp
if_2_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 2
add dword ptr [rbx + 4 ], 1
Return_Here_9:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov rcx, rcx
sub dword ptr [rcx + 4 ], 1
Return_Here_12:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov rcx, rcx
if_4:
mov r8d, dword ptr [rcx + 4 ]
cmp r8d, 0
jle if_4_END
mov r8d, 0
jmp Return_Here_13
if_4_END:
mov rcx, qword ptr [rcx + 8 ]
mov ecx, dword ptr [rcx + 0 * 4 ]
mov r8d, ecx
jmp Return_Here_13
Return_Here_13:
mov eax, r8d
add rsp, 184
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
pop r14
pop r15
ret 
add rsp, 184
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
pop r14
pop r15
ret 


main:
push r15
push r14
push r13
push r12
push rbp
push rsi
push rdi
push rbx
sub rsp, 32
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov rbx, rcx
mov dword ptr [rbx + 0 ], 1
mov dword ptr [rbx + 4 ], 0
mov ecx, dword ptr [rbx + 0 ]
mov ecx, ecx
mov r8d, ecx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
mov ecx, ecx
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax
jmp Return_Here_15
Return_Here_15:
mov rcx, qword ptr [rsp + 24 ]
mov qword ptr [rbx + 8 ], rcx
jmp Return_Here_16
Return_Here_16:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
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
mov edi, ecx
mov ecx, edi
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, edi
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rsi, rax
jmp Return_Here_17
Return_Here_17:
mov rbp, rsi
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov r12d, ecx
mov rcx, qword ptr [rbx + 8 ]
mov r13, rcx
mov r14, rbp
mov r15d, 0
cmp r15d, r12d
jge while_6_END
while_6:
lea rcx, qword ptr [r14 + r15 * 4 ]
mov r8d, dword ptr [r13 + r15 * 4 ]
mov dword ptr [rcx ], r8d
mov dword ptr [rsp + 0 ], 
mov dword ptr [rsp + 0 ], r15d
add r15d, 1
cmp r15d, r12d
jge while_6_END
jmp while_6
while_6_END:
jmp Return_Here_18
Return_Here_18:
mov qword ptr [rcx + 8 ], rbp
if_5_END:
mov r8, qword ptr [rcx + 8 ]
mov r9d, dword ptr [rcx + 4 ]
lea r8, qword ptr [r8 + r9 * 4 ]
mov dword ptr [r8 ], 5
add dword ptr [rcx + 4 ], 1
Return_Here_19:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov qword ptr [rsp + 0 ], 
mov qword ptr [rsp + 0 ], rcx
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
mov edi, ecx
mov ecx, edi
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, edi
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rsi, rax
jmp Return_Here_20
Return_Here_20:
mov rbp, rsi
mov ecx, dword ptr [rbx + 4 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov r12d, ecx
mov rcx, qword ptr [rbx + 8 ]
mov r13, rcx
mov r14, rbp
mov r15d, 0
cmp r15d, r12d
jge while_8_END
while_8:
lea rcx, qword ptr [r14 + r15 * 4 ]
mov r8d, dword ptr [r13 + r15 * 4 ]
mov dword ptr [rcx ], r8d
mov ecx, r15d
add r15d, 1
cmp r15d, r12d
jge while_8_END
jmp while_8
while_8_END:
jmp Return_Here_21
Return_Here_21:
mov qword ptr [rbx + 8 ], rbp
if_7_END:
mov rcx, qword ptr [rbx + 8 ]
mov r8d, dword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 2
add dword ptr [rbx + 4 ], 1
Return_Here_22:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov rcx, rcx
sub dword ptr [rcx + 4 ], 1
Return_Here_23:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov rcx, rcx
if_9:
mov r8d, dword ptr [rcx + 4 ]
cmp r8d, 0
jle if_9_END
mov r8d, 0
jmp Return_Here_24
if_9_END:
mov rcx, qword ptr [rcx + 8 ]
mov ecx, dword ptr [rcx + 0 * 4 ]
mov r8d, ecx
jmp Return_Here_24
Return_Here_24:
jmp Return_Here_14
Return_Here_14:
mov eax, 1
add rsp, 32
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
pop r14
pop r15
ret 
add rsp, 32
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
pop r14
pop r15
ret 


Destructor:
push rbx
if_10:
cmp rcx, 0
je if_10_END
mov r8, qword ptr [rcx + 16 ]
sub r8, 1
cmp r8, 1
jge if_10_END
mov r8, rcx
add qword ptr [r8 + 16 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_3:
mov rcx, rbx
call Destructor
if_10_END:
pop rbx
ret 


.section .data
