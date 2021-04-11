.intel_syntax noprefix
.global main
.section .text
.List_int__:
mov r8d, dword ptr [rcx + 0 ]
mov r8d, dword ptr [rcx + 0 ]
mov eax, 4
mul r8d
mov r8d, eax
mov ecx, r8d
call _Z8allocatei
mov qword ptr [rcx + 4 ], rax
mov rax, rcx
ret 
ret 


main:
push rbx
mov rcx, rbx
call .List_int__
mov rcx, qword ptr [rbx + 4 ]
lea rcx, qword ptr [rcx + 1 * 4 ]
mov eax, dword ptr [rcx ]
pop rbx
ret 
pop rbx
ret 


.section .data
