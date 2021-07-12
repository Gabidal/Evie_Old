.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
sub rsp, 72
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 0 ], 1
mov r8, r8
mov r8, rcx
mov dword ptr [r8 + 8 ], 4
Return_Here_4:
mov dword ptr [rcx + 12 ], 1
mov dword ptr [rcx + 16 ], 2
mov dword ptr [rcx + 20 ], 6
mov dword ptr [rcx + 8 ], 5
jmp Return_Here_3
Return_Here_3:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 0 ], 1
mov r8, r8
mov r8, rcx
jmp Return_Here_6
Return_Here_6:
mov ecx, dword ptr [r8 + 12 ]
mov ecx, ecx
jmp Return_Here_5
Return_Here_5:
mov eax, ecx
add rsp, 72
ret 
add rsp, 72
ret 


_Z4mainv:
sub rsp, 48
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 0 ], 1
mov r8, r8
mov r8, rcx
mov dword ptr [r8 + 8 ], 4
Return_Here_8:
mov dword ptr [rcx + 12 ], 1
mov dword ptr [rcx + 16 ], 2
mov dword ptr [rcx + 20 ], 6
mov dword ptr [rcx + 8 ], 5
jmp Return_Here_9
Return_Here_9:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 0 ], 1
mov r8, r8
mov r8, rcx
jmp Return_Here_10
Return_Here_10:
mov ecx, dword ptr [r8 + 12 ]
mov ecx, ecx
jmp Return_Here_11
Return_Here_11:
jmp Return_Here_7
Return_Here_7:
mov eax, 1
add rsp, 48
ret 
add rsp, 48
ret 


_ZN6Banana10DestructorEP6Banana:
push rbx
if_0:
cmp rcx, 0
je if_0_END
mov r8, qword ptr [rcx + 0 ]
sub r8, 1
cmp r8, 1
jge if_0_END
mov r8, rcx
add qword ptr [r8 + 0 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, r8d
call _V19internal_deallocatePhx
Return_Here_0:
mov rcx, rbx
call _ZN6Banana10DestructorEP6Banana
if_0_END:
pop rbx
ret 


.section .data
