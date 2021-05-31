.intel_syntax noprefix
.global main
.global Start_Test
.section .text
banana:
mov eax, 1
ret 
ret 


Start_Test:
sub rsp, 24
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call ____List_int_
call banana
mov eax, eax
add rsp, 24
ret 
add rsp, 24
ret 


main:
mov eax, 1
ret 
ret 


char:
mov rax, rcx
ret 
ret 


____Deallocate_BYTE_POINTER_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
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


____List_int_:
push rbx
mov rbx, rcx
mov dword ptr [rbx + 20 ], 1
mov dword ptr [rbx + 16 ], 0
mov ecx, dword ptr [rbx + 20 ]
mov ecx, ecx
call ____Allocate_int_
mov qword ptr [rbx + 8 ], rax
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


____memcpy_int_:
mov r9d, 0
cmp r9d, r8d
jge while5558_END
while5558:
lea r10, qword ptr [rcx + r9 * 4 ]
mov r11d, dword ptr [rdx + r9 * 4 ]
mov dword ptr [r10 ], r11d
add r9d, 1
cmp r9d, r8d
jge while5558_END
jmp while5558
while5558_END:
ret 
ret 


____Deallocate_____List_int__:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


.section .data
