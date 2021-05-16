.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
sub rsp, 24
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call .List_int_
lea rcx, qword ptr [rsp ]
mov rcx, rcx
mov edx, 5
call .Add_int_
lea rcx, qword ptr [rsp ]
mov rcx, rcx
mov edx, 2
call .Add_int_
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Pop_Back
mov rcx, qword ptr [rsp + 16 ]
lea rcx, qword ptr [rcx + 0 * 4 ]
mov eax, dword ptr [rcx ]
add rsp, 24
ret 
add rsp, 24
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


.Add_int_:
push rbp
push rsi
push rdi
push rbx
mov rdi, rcx
mov ebx, edx
if1112:
mov ecx, dword ptr [rdi + 12 ]
mov r8d, dword ptr [rdi + 8 ]
cmp ecx, r8d
jl if1112_END
mov ecx, dword ptr [rdi + 12 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [rdi + 8 ], ecx
mov ecx, dword ptr [rdi + 8 ]
mov ecx, ecx
call .Allocate_int_
mov rsi, rax
mov rcx, rsi
mov r8, qword ptr [rdi + 16 ]
mov rdx, r8
mov r8d, dword ptr [rdi + 12 ]
mov rbp, rdx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
mov r8d, r8d
call .memcpy_int_
mov qword ptr [rdi + 16 ], rsi
if1112_END:
mov rcx, qword ptr [rdi + 16 ]
mov r8d, dword ptr [rdi + 12 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], ebx
add dword ptr [rdi + 12 ], 1
pop rbx
pop rdi
pop rsi
pop rbp
ret 


Pop_Back:
add dword ptr [rcx + 12 ], 1
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
jge while13_END
while13:
lea r10, qword ptr [rcx + r9 * 4 ]
mov r11d, dword ptr [rdx + r9 * 4 ]
mov dword ptr [r10 ], r11d
add r9d, 1
cmp r9d, r8d
jge while13_END
jmp while13
while13_END:
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
