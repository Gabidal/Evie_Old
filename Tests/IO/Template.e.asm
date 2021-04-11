.intel_syntax noprefix
.global main
.global Start_Test
.section .text
.List_int__:
push rbx
mov rbx, rcx
mov dword ptr [rbx + 0 ], 1
mov ecx, dword ptr [rbx + 0 ]
mov eax, 4
mul ecx
mov ecx, eax
mov ecx, ecx
call _Z8allocatei
mov qword ptr [rbx + 4 ], rax
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


Start_Test:
sub rsp, 12
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call .List_int__
mov rcx, qword ptr [rsp + 4 ]
lea rcx, qword ptr [rcx + 1 * 4 ]
mov dword ptr [rcx ], 5
mov rcx, qword ptr [rsp + 4 ]
lea rcx, qword ptr [rcx + 1 * 4 ]
mov eax, dword ptr [rcx ]
add rsp, 12
ret 
add rsp, 12
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


.section .data
