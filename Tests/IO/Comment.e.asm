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
call .List_int_
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


int:
mov rax, rcx
ret 
ret 


char:
mov rax, rcx
ret 
ret 


.Allocate_int_:
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


.memcpy_int_:
mov r9d, 0
cmp r9d, r8d
jge while21_END
while21:
lea r10, qword ptr [rcx + r9 * 4 ]
mov r11d, dword ptr [rdx + r9 * 4 ]
mov dword ptr [r10 ], r11d
add r9d, 1
cmp r9d, r8d
jge while21_END
jmp while21
while21_END:
ret 
ret 


.List_int_:
push rbx
mov rbx, rcx
mov dword ptr [rbx + 8 ], 1
mov dword ptr [rbx + 12 ], 0
mov ecx, dword ptr [rbx + 8 ]
mov ecx, ecx
call .Allocate_int_
mov qword ptr [rbx + 16 ], rax
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


.section .data
