.intel_syntax noprefix
.global main
.section .text
.List_int__:
mov r8d, dword ptr [rcx + 0 ]
mov eax, 4
mul dword ptr [rcx + 0 ]
mov dword ptr [rcx + 0 ], eax
mov ecx, dword ptr [rcx + 0 ]
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
