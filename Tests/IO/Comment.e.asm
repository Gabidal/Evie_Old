.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
push rbx
sub rsp, 96
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
jmp Return_Here_60
Return_Here_60:
mov rcx, qword ptr [rsp + 24 ]
mov qword ptr [rbx + 8 ], rcx
jmp Return_Here_59
Return_Here_59:
mov ecx, 1
jmp Return_Here_61
Return_Here_61:
mov eax, ecx
add rsp, 96
pop rbx
ret 
add rsp, 96
pop rbx
ret 


_Z4mainv:
mov eax, 1
ret 
ret 


_ZN13____List_int_10DestructorEP13____List_int_:
push rbx
if_21:
cmp rcx, 0
je if_21_END
mov r8, qword ptr [rcx + 16 ]
sub r8, 1
cmp r8, 1
jge if_21_END
mov r8, rcx
add qword ptr [r8 + 16 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_58:
mov rcx, rbx
call _ZN13____List_int_10DestructorEP13____List_int_
if_21_END:
pop rbx
ret 


.section .data
