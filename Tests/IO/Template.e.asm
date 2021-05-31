.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
sub rsp, 24
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call ____List_int_
lea rcx, qword ptr [rsp ]
mov rcx, rcx
mov edx, 5
call ____Add_int_
lea rcx, qword ptr [rsp ]
mov rcx, rcx
mov edx, 2
call ____Add_int_
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Pop_Back
mov rcx, qword ptr [rsp + 8 ]
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


____Add_int_:
push rbp
push rsi
push rdi
push rbx
mov rdi, rcx
mov ebx, edx
if3740:
mov ecx, dword ptr [rdi + 16 ]
mov r8d, dword ptr [rdi + 20 ]
cmp ecx, r8d
jl if3740_END
mov ecx, dword ptr [rdi + 16 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [rdi + 20 ], ecx
mov ecx, dword ptr [rdi + 20 ]
mov ecx, ecx
call ____Allocate_int_
mov rsi, rax
mov rcx, rsi
mov r8, qword ptr [rdi + 8 ]
mov rdx, r8
mov r8d, dword ptr [rdi + 16 ]
mov rbp, rdx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
mov r8d, r8d
call ____memcpy_int_
mov qword ptr [rdi + 8 ], rsi
if3740_END:
mov rcx, qword ptr [rdi + 8 ]
mov r8d, dword ptr [rdi + 16 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], ebx
add dword ptr [rdi + 16 ], 1
pop rbx
pop rdi
pop rsi
pop rbp
ret 


Pop_Back:
add dword ptr [rcx + 16 ], 1
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
jge while3841_END
while3841:
lea r10, qword ptr [rcx + r9 * 4 ]
mov r11d, dword ptr [rdx + r9 * 4 ]
mov dword ptr [r10 ], r11d
add r9d, 1
cmp r9d, r8d
jge while3841_END
jmp while3841
while3841_END:
ret 
ret 


____Deallocate_____List_int__:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


.section .data
