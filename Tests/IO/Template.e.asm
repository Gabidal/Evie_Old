.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
sub rsp, 16
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call .List_int__
mov rcx, qword ptr [rsp + 8 ]
lea rcx, qword ptr [rcx + 1 * 4 ]
mov dword ptr [rcx ], 5
mov rcx, qword ptr [rsp + 8 ]
lea rcx, qword ptr [rcx + 1 * 4 ]
mov eax, dword ptr [rcx ]
add rsp, 16
ret 
add rsp, 16
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


.memcpy_int__:
mov r9d, 0
cmp r9d, r8d
jge while_END
while:
lea r10, qword ptr [rcx + r9 * 4 ]
mov r11d, dword ptr [rdx + r9 * 4 ]
mov dword ptr [r10 ], r11d
mov r10d, r9d
add r9d, 1
cmp r9d, r8d
jge while_END
jmp while
while_END:
ret 
ret 


.List_int__:
push rbx
mov rbx, rcx
mov dword ptr [rbx + 0 ], 1
mov dword ptr [rbx + 4 ], 0
mov ecx, dword ptr [rbx + 0 ]
mov eax, 4
mul ecx
mov ecx, eax
mov ecx, ecx
call _Z8allocatei
mov qword ptr [rbx + 8 ], rax
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


.section .data
