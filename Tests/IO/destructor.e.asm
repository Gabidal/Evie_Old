.intel_syntax noprefix
.global Start_Test
.global main
.section .text
main:
mov eax, 1
ret 
ret 


Start_Test:
push rbx
sub rsp, 48
mov ecx, 8
call _V17internal_allocatex_rPh
mov rcx, rax
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
jmp Return_Here_5
Return_Here_5:
mov r8, rcx
add qword ptr [r8 + 0 ], 1
mov r8, r8
mov r8, rcx
mov dword ptr [r8 + 0 ], 1
mov dword ptr [r8 + 4 ], 2
mov rcx, r8
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov rcx, r8
jmp Return_Here_9
Return_Here_9:
mov r8, qword ptr [rcx + 0 ]
mov qword ptr [rsp + 0 ], r8
mov rcx, qword ptr [rcx + 8 ]
mov qword ptr [rsp + 8 ], rcx
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov r8d, dword ptr [rcx + 12 ]
mov ebx, r8d
mov rcx, rcx
if_0:
cmp rcx, 0
je if_0_END
mov r8, qword ptr [rcx + 0 ]
sub r8, 1
cmp r8, 1
jge if_0_END
mov rcx, rcx
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_8:
if_0_END:
Return_Here_13:
mov eax, ebx
add rsp, 48
pop rbx
ret 
add rsp, 48
pop rbx
ret 


int:
mov rax, rcx
ret 
ret 


short:
mov rax, rcx
ret 
ret 


char:
mov rax, rcx
ret 
ret 


float:
movsd xmm0, xmm0
ret 
ret 


double:
movsd xmm0, xmm0
ret 
ret 


long:
mov rax, rcx
ret 
ret 


string:
mov rax, rcx
ret 
ret 


BYTE_POINTER:
mov r8, rcx
jmp Return_Here_17
Return_Here_17:
mov rax, rcx
ret 
ret 


foo:
mov dword ptr [rcx + 12 ], 1
mov dword ptr [rcx + 8 ], 2
mov rax, rcx
ret 
ret 


____Deallocate_foo_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


.section .data
