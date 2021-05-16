.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
push rbx
sub rsp, 16
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Banana
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Get
mov ebx, eax
lea rcx, qword ptr [rsp ]
mov rcx, rcx
mov edx, 1
call Set
add ebx, eax
mov ecx, ebx
mov r8d, dword ptr [rip + Banana_Y ]
mov r9d, dword ptr [rip + Apple_Y ]
add r8d, r9d
sub r8d, ecx
mov eax, r8d
add rsp, 16
pop rbx
ret 
add rsp, 16
pop rbx
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


Get:
mov r8d, dword ptr [rip + Banana_Y ]
mov ecx, dword ptr [rcx + 8 ]
add r8d, ecx
mov eax, r8d
ret 
ret 


char:
mov rax, rcx
ret 
ret 


Banana:
mov dword ptr [rcx + 8 ], 1
mov rax, rcx
ret 
ret 


Set:
mov dword ptr [rcx + 8 ], edx
add dword ptr [rcx + 8 ], 1
mov eax, dword ptr [rcx + 8 ]
ret 
ret 


.section .data
Banana_Y:
.long 2
Apple_X:
.long 2
Apple_Y:
.long 3
