.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
push r15
push r14
push r13
push r12
push rbp
push rsi
push rdi
push rbx
sub rsp, 192
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
mov dword ptr [rbx + 8 ], 1
mov dword ptr [rbx + 12 ], 0
mov ecx, dword ptr [rbx + 8 ]
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
jmp Return_Here_18
Return_Here_18:
mov rcx, qword ptr [rsp + 24 ]
mov qword ptr [rbx + 16 ], rcx
jmp Return_Here_17
Return_Here_17:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_1:
mov ecx, dword ptr [rbx + 12 ]
mov r8d, dword ptr [rbx + 8 ]
cmp ecx, r8d
jl if_1_END
mov ecx, dword ptr [rbx + 12 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [rbx + 8 ], ecx
mov ecx, dword ptr [rbx + 8 ]
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
mov ecx, dword ptr [rbx + 12 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov r12d, ecx
mov rcx, qword ptr [rbx + 16 ]
mov r13, rcx
mov r14, rbp
mov r15d, 0
cmp r15d, r12d
jge while_2_END
while_2:
lea rcx, qword ptr [r14 + r15 * 4 ]
mov r8d, dword ptr [r13 + r15 * 4 ]
mov dword ptr [rcx ], r8d
add r15d, 1
cmp r15d, r12d
jge while_2_END
jmp while_2
while_2_END:
jmp Return_Here_21
Return_Here_21:
mov qword ptr [rbx + 16 ], rbp
if_1_END:
mov rcx, qword ptr [rbx + 16 ]
mov r8d, dword ptr [rbx + 12 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 5
add dword ptr [rbx + 12 ], 1
Return_Here_19:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rbx, rcx
if_3:
mov ecx, dword ptr [rbx + 12 ]
mov r8d, dword ptr [rbx + 8 ]
cmp ecx, r8d
jl if_3_END
mov ecx, dword ptr [rbx + 12 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [rbx + 8 ], ecx
mov ecx, dword ptr [rbx + 8 ]
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
jmp Return_Here_23
Return_Here_23:
mov rbp, rsi
mov ecx, dword ptr [rbx + 12 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov r12d, ecx
mov rcx, qword ptr [rbx + 16 ]
mov r13, rcx
mov r14, rbp
mov r15d, 0
cmp r15d, r12d
jge while_4_END
while_4:
lea rcx, qword ptr [r14 + r15 * 4 ]
mov r8d, dword ptr [r13 + r15 * 4 ]
mov dword ptr [rcx ], r8d
add r15d, 1
cmp r15d, r12d
jge while_4_END
jmp while_4
while_4_END:
jmp Return_Here_24
Return_Here_24:
mov qword ptr [rbx + 16 ], rbp
if_3_END:
mov rcx, qword ptr [rbx + 16 ]
mov r8d, dword ptr [rbx + 12 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 2
add dword ptr [rbx + 12 ], 1
Return_Here_22:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
sub dword ptr [rcx + 12 ], 1
Return_Here_25:
mov ecx, 0
lea r8, qword ptr [rsp ]
mov r8, r8
add qword ptr [r8 + 0 ], 1
mov r8, r8
if_5:
mov r9d, dword ptr [r8 + 12 ]
cmp ecx, r9d
jle if_5_END
mov ecx, 0
jmp Return_Here_26
if_5_END:
mov r8, qword ptr [r8 + 16 ]
mov r8d, dword ptr [r8 + 0 * 4 ]
mov ecx, r8d
jmp Return_Here_26
Return_Here_26:
mov eax, ecx
add rsp, 192
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
pop r14
pop r15
ret 
add rsp, 192
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
pop r13
pop r14
pop r15
ret 


_Z4mainv:
jmp _Z10Start_Testv
mov eax, 1
ret 
ret 


_ZN13____List_int_10DestructorEP13____List_int_:
push rbx
if_6:
cmp rcx, 0
je if_6_END
mov r8, qword ptr [rcx + 0 ]
sub r8, 1
cmp r8, 1
jge if_6_END
mov r8, rcx
add qword ptr [r8 + 0 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_16:
mov rcx, rbx
call _ZN13____List_int_10DestructorEP13____List_int_
if_6_END:
pop rbx
ret 


.section .data
