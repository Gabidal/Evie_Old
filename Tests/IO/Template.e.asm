.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
push rdi
push rbx
sub rsp, 144
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
mov dword ptr [ + 0 ], 1
mov dword ptr [ + 4 ], 0
mov ecx, dword ptr [ + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov qword ptr [ + 8 ], rax
jmp .Return_Here_0
mov , 5
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
if_0:
mov ecx, dword ptr [ + 4 ]
mov r8d, dword ptr [ + 0 ]
cmp ecx, r8d
jl if_0_END
mov ecx, dword ptr [ + 4 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [ + 0 ], ecx
mov ecx, dword ptr [ + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rbx, rax
mov rcx, rbx
mov r8, qword ptr [ + 8 ]
mov rdx, r8
mov r8d, dword ptr [ + 4 ]
mov rdi, rdx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
mov r8d, r8d
call ____memcpy_int_
mov qword ptr [ + 8 ], rbx
if_0_END:
mov rcx, qword ptr [ + 8 ]
mov r8d, dword ptr [ + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov r8d, 
mov dword ptr [rcx ], r8d
add dword ptr [ + 4 ], 1
mov , 2
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
if_1:
mov ecx, dword ptr [ + 4 ]
mov r8d, dword ptr [ + 0 ]
cmp ecx, r8d
jl if_1_END
mov ecx, dword ptr [ + 4 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [ + 0 ], ecx
mov ecx, dword ptr [ + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rbx, rax
mov rcx, rbx
mov r8, qword ptr [ + 8 ]
mov rdx, r8
mov r8d, dword ptr [ + 4 ]
mov rdi, rdx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
mov r8d, r8d
call ____memcpy_int_
mov qword ptr [ + 8 ], rbx
if_1_END:
mov rcx, qword ptr [ + 8 ]
mov r8d, dword ptr [ + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov r8d, 
mov dword ptr [rcx ], r8d
add dword ptr [ + 4 ], 1
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
sub dword ptr [ + 4 ], 1
mov , 0
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
if_2:
mov ecx, dword ptr [ + 4 ]
cmp , ecx
jle if_2_END
mov eax, 0
add rsp, 144
pop rbx
pop rdi
ret 
if_2_END:
mov rcx, qword ptr [ + 8 ]
lea rcx, qword ptr [rcx +  * 4 ]
mov eax, dword ptr [rcx ]
add rsp, 144
pop rbx
pop rdi
ret 
add rsp, 144
pop rbx
pop rdi
ret 


main:
push rdi
push rbx
sub rsp, 24
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
mov dword ptr [ + 0 ], 1
mov dword ptr [ + 4 ], 0
mov ecx, dword ptr [ + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov qword ptr [ + 8 ], rax
jmp .Return_Here_0
mov , 5
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
if_3:
mov ecx, dword ptr [ + 4 ]
mov r8d, dword ptr [ + 0 ]
cmp ecx, r8d
jl if_3_END
mov ecx, dword ptr [ + 4 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [ + 0 ], ecx
mov ecx, dword ptr [ + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rbx, rax
mov rcx, rbx
mov r8, qword ptr [ + 8 ]
mov rdx, r8
mov r8d, dword ptr [ + 4 ]
mov rdi, rdx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
mov r8d, r8d
call ____memcpy_int_
mov qword ptr [ + 8 ], rbx
if_3_END:
mov rcx, qword ptr [ + 8 ]
mov r8d, dword ptr [ + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov r8d, 
mov dword ptr [rcx ], r8d
add dword ptr [ + 4 ], 1
mov , 2
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
if_4:
mov ecx, dword ptr [ + 4 ]
mov r8d, dword ptr [ + 0 ]
cmp ecx, r8d
jl if_4_END
mov ecx, dword ptr [ + 4 ]
mov r8, rdx
mov eax, 2
mul ecx
mov ecx, eax
mov rdx, r8
mov dword ptr [ + 0 ], ecx
mov ecx, dword ptr [ + 0 ]
mov ecx, ecx
call ____Allocate_int_
mov rbx, rax
mov rcx, rbx
mov r8, qword ptr [ + 8 ]
mov rdx, r8
mov r8d, dword ptr [ + 4 ]
mov rdi, rdx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
mov r8d, r8d
call ____memcpy_int_
mov qword ptr [ + 8 ], rbx
if_4_END:
mov rcx, qword ptr [ + 8 ]
mov r8d, dword ptr [ + 4 ]
lea rcx, qword ptr [rcx + r8 * 4 ]
mov r8d, 
mov dword ptr [rcx ], r8d
add dword ptr [ + 4 ], 1
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
sub dword ptr [ + 4 ], 1
mov , 0
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov , rcx
if_5:
mov ecx, dword ptr [ + 4 ]
cmp , ecx
jle if_5_END
jmp .Return_Here_5
if_5_END:
jmp .Return_Here_5
mov eax, 1
add rsp, 24
pop rbx
pop rdi
ret 
add rsp, 24
pop rbx
pop rdi
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


____memcpy_int_:
mov r9d, 0
cmp r9d, r8d
jge while_6_END
while_6:
lea r10, qword ptr [rcx + r9 * 4 ]
mov r11d, dword ptr [rdx + r9 * 4 ]
mov dword ptr [r10 ], r11d
add r9d, 1
cmp r9d, r8d
jge while_6_END
jmp while_6
while_6_END:
ret 
ret 


____Deallocate_____List_int__:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


.section .data
