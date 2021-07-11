.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
push rsi
push rdi
push rbx
sub rsp, 64
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov dword ptr [rcx + 0 ], 1
jmp Return_Here_47
Return_Here_47:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov ebx, dword ptr [rip + Banana_Y ]
mov r8d, dword ptr [rcx + 0 ]
add ebx, r8d
mov r8d, ebx
jmp Return_Here_45
Return_Here_45:
lea r9, qword ptr [rsp ]
mov r9, r9
add qword ptr [r9 + 8 ], 1
mov rdi, r9
mov dword ptr [rdi + 0 ], 1
mov r9d, dword ptr [rdi + 0 ]
add r9d, 1
mov r9d, r9d
jmp Return_Here_46
Return_Here_46:
mov r8d, r8d
add r8d, r9d
mov esi, r8d
mov rcx, rcx
call _ZN6Banana10DestructorEP6Banana
mov rcx, rdi
call _ZN6Banana10DestructorEP6Banana
mov ebx, dword ptr [rip + Banana_Y ]
mov ecx, dword ptr [rip + Apple_Y ]
add ebx, ecx
sub ebx, esi
mov eax, ebx
add rsp, 64
pop rbx
pop rdi
pop rsi
ret 
add rsp, 64
pop rbx
pop rdi
pop rsi
ret 


_Z4mainv:
push rbx
sub rsp, 32
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov dword ptr [rcx + 0 ], 1
jmp Return_Here_49
Return_Here_49:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov r8d, dword ptr [rip + Banana_Y ]
mov r9d, dword ptr [rcx + 0 ]
add r8d, r9d
mov r8d, r8d
jmp Return_Here_50
Return_Here_50:
lea r9, qword ptr [rsp ]
mov r9, r9
add qword ptr [r9 + 8 ], 1
mov rbx, r9
mov dword ptr [rbx + 0 ], 1
mov r9d, dword ptr [rbx + 0 ]
add r9d, 1
mov r9d, r9d
jmp Return_Here_51
Return_Here_51:
mov r8d, r8d
add r8d, r9d
mov r8d, r8d
mov rcx, rcx
call _ZN6Banana10DestructorEP6Banana
mov rcx, rbx
call _ZN6Banana10DestructorEP6Banana
jmp Return_Here_48
Return_Here_48:
mov eax, 1
add rsp, 32
pop rbx
ret 
add rsp, 32
pop rbx
ret 


_ZN6Banana10DestructorEP6Banana:
push rbx
if_20:
cmp rcx, 0
je if_20_END
mov r8, qword ptr [rcx + 8 ]
sub r8, 1
cmp r8, 1
jge if_20_END
mov r8, rcx
add qword ptr [r8 + 8 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_44:
mov rcx, rbx
call _ZN6Banana10DestructorEP6Banana
if_20_END:
pop rbx
ret 


.section .data
Banana_Y:
.long 2
Apple_X:
.long 2
Apple_Y:
.long 3
