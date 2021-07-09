.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
push rdi
push rbx
sub rsp, 64
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov dword ptr [rcx + 0 ], 1
jmp Return_Here_35
Return_Here_35:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rbx, rcx
jmp Return_Here_33
Return_Here_33:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rdi, rcx
mov dword ptr [rdi + 0 ], 1
jmp Return_Here_34
Return_Here_34:
mov rcx, rbx
call Destructor
mov rcx, rdi
call Destructor
mov ecx, dword ptr [rip + Banana_Y ]
mov r8d, dword ptr [rip + Apple_Y ]
add ecx, r8d
mov ecx, dword ptr [rip + Banana_Y ]
mov r8d, dword ptr [rbx + 0 ]
add ecx, r8d
mov r8d, dword ptr [rdi + 0 ]
add r8d, 1
add ecx, r8d
sub ecx, ecx
mov eax, ecx
add rsp, 64
pop rbx
pop rdi
ret 
add rsp, 64
pop rbx
pop rdi
ret 


main:
push rbx
sub rsp, 32
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
mov dword ptr [rcx + 0 ], 1
jmp Return_Here_37
Return_Here_37:
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 8 ], 1
mov rcx, rcx
jmp Return_Here_38
Return_Here_38:
lea r8, qword ptr [rsp ]
mov r8, r8
add qword ptr [r8 + 8 ], 1
mov rbx, r8
mov dword ptr [rbx + 0 ], 1
jmp Return_Here_39
Return_Here_39:
mov rcx, rcx
call Destructor
mov rcx, rbx
call Destructor
jmp Return_Here_36
Return_Here_36:
mov eax, 1
add rsp, 32
pop rbx
ret 
add rsp, 32
pop rbx
ret 


Destructor:
push rbx
if_7:
cmp rcx, 0
je if_7_END
mov r8, qword ptr [rcx + 8 ]
sub r8, 1
cmp r8, 1
jge if_7_END
mov r8, rcx
add qword ptr [r8 + 8 ], 1
mov rbx, r8
mov rbx, rcx
mov rcx, rbx
mov edx, 8
call _V19internal_deallocatePhx
Return_Here_32:
mov rcx, rbx
call Destructor
if_7_END:
pop rbx
ret 


.section .data
Banana_Y:
.long 2
Apple_X:
.long 2
Apple_Y:
.long 3
