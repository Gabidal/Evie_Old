.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
sub rsp, 72
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 4 ], 1
mov r8, r8
mov r8, rcx
mov dword ptr [r8 + 0 ], 4
Return_Here_67:
mov dword ptr [rcx + 4 ], 1
mov dword ptr [rcx + 8 ], 2
mov dword ptr [rcx + 12 ], 6
mov dword ptr [rcx + 0 ], 5
jmp Return_Here_66
Return_Here_66:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 4 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 16 ], 1
mov r8, r8
mov r8, rcx
jmp Return_Here_69
Return_Here_69:
mov ecx, dword ptr [r8 + 4 ]
mov ecx, ecx
jmp Return_Here_68
Return_Here_68:
mov eax, ecx
add rsp, 72
ret 
add rsp, 72
ret 


_Z4mainv:
sub rsp, 48
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 16 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 4 ], 1
mov r8, r8
mov r8, rcx
mov dword ptr [r8 + 0 ], 4
Return_Here_71:
mov dword ptr [rcx + 4 ], 1
mov dword ptr [rcx + 8 ], 2
mov dword ptr [rcx + 12 ], 6
mov dword ptr [rcx + 0 ], 5
jmp Return_Here_72
Return_Here_72:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 4 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 16 ], 1
mov r8, r8
mov r8, rcx
jmp Return_Here_73
Return_Here_73:
mov ecx, dword ptr [r8 + 4 ]
mov ecx, ecx
jmp Return_Here_74
Return_Here_74:
jmp Return_Here_70
Return_Here_70:
mov eax, 1
add rsp, 48
ret 
add rsp, 48
ret 


_ZN6Banana10DestructorEP6Banana:
push rbx
if_22:
cmp rcx, 0
je if_22_END
mov r8, qword ptr [rcx + 16 ]
sub r8, 1
cmp r8, 1
jge if_22_END
mov r8, rcx
add qword ptr [r8 + 16 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, r8d
call _V19internal_deallocatePhx
Return_Here_63:
mov rcx, rbx
call _ZN6Banana10DestructorEP6Banana
if_22_END:
pop rbx
ret 


.section .data
