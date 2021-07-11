.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
sub rsp, 48
Return_Here_20:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov r8, rcx
add qword ptr [r8 + 4 ], 1
mov r8, r8
mov r8, rcx
mov dword ptr [r8 + 0 ], 0
jmp Return_Here_23
Return_Here_23:
mov dword ptr [rcx + 0 ], 1
mov r8d, 1074261268
mov dword ptr [rcx + 4 ], r8d
jmp Return_Here_22
Return_Here_22:
movss xmm0, dword ptr [rsp + 4 ]
cvttss2si ecx, xmm0
mov eax, ecx
add rsp, 48
ret 
add rsp, 48
ret 


_Z4mainv:
mov eax, 1
ret 
ret 


_ZN4Base10DestructorEP4Base:
push rbx
if_6:
cmp rcx, 0
je if_6_END
mov r8, qword ptr [rcx + 4 ]
sub r8, 1
cmp r8, 1
jge if_6_END
mov r8, rcx
add qword ptr [r8 + 4 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_17:
mov rcx, rbx
call _ZN4Base10DestructorEP4Base
if_6_END:
pop rbx
ret 


_ZN3Mid10DestructorEP3Mid:
push rbx
if_7:
cmp rcx, 0
je if_7_END
mov r8, qword ptr [rcx + 8 ]
sub r8, 1
cmp r8, 1
jge if_7_END
mov r8, rcx
add qword ptr [r8 + 8 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_18:
mov rcx, rbx
call _ZN3Mid10DestructorEP3Mid
if_7_END:
pop rbx
ret 


_ZN3Top10DestructorEP3Top:
push rbx
if_8:
cmp rcx, 0
je if_8_END
mov r8, qword ptr [rcx + 12 ]
sub r8, 1
cmp r8, 1
jge if_8_END
mov r8, rcx
add qword ptr [r8 + 8 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_19:
mov rcx, rbx
call _ZN3Top10DestructorEP3Top
if_8_END:
pop rbx
ret 


.section .data
