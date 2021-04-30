.intel_syntax noprefix
.global main
.section .text
main:
push rbx
mov rdi, rbx
call .List_int_
mov rcx, qword ptr [rbx + 8 ]
lea rcx, qword ptr [rcx + 1 * 4 ]
mov eax, dword ptr [rcx ]
pop rbx
ret 
pop rbx
ret 


.memcpy_int_:
mov ecx, 0
cmp ecx, edx
jge while2_END
while2:
lea r8, qword ptr [rdi + rcx * 4 ]
mov r9d, dword ptr [rsi + rcx * 4 ]
mov dword ptr [r8 ], r9d
add ecx, 1
cmp ecx, edx
jge while2_END
jmp while2
while2_END:
ret 
ret 


.List_int_:
push rbx
mov rbx, rdi
mov dword ptr [rbx + 0 ], 1
mov dword ptr [rbx + 4 ], 0
mov ecx, dword ptr [rbx + 0 ]
mov rdi, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, rdi
mov edi, ecx
call _Z8allocatei
mov qword ptr [rbx + 8 ], rax
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


.section .data
