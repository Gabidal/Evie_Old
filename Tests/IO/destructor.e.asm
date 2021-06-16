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
jmp Return_Here_5
Return_Here_5:
mov rcx, rcx
call foo
mov rcx, qword ptr [rax + 0 ]
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rax + 8 ]
mov qword ptr [rsp + 8 ], rcx
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov r8d, dword ptr [rcx + 12 ]
mov ebx, r8d
mov r8, rcx
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov r8, rcx
if_0:
cmp r8, 0
je if_0_END
mov rcx, qword ptr [r8 + 0 ]
sub rcx, 1
cmp rcx, 1
jge if_0_END
mov rcx, r8
mov r8, r8
add qword ptr [r8 + 0 ], 1
mov rcx, r8
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_6:
if_0_END:
Return_Here_9:
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
jmp Return_Here_13
Return_Here_13:
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
