.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Banana:
mov dword ptr [rcx + 0 ], 1
mov rax, rcx
ret 
ret 


Get:
mov r8d, dword ptr [rip + Banana_Y ]
mov ecx, dword ptr [rcx + 0 ]
add r8d, ecx
mov eax, r8d
ret 
ret 


Start_Test:
sub rsp, 8
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Banana
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Get
mov ecx, eax
mov r8d, dword ptr [rip + Banana_Y ]
mov r9d, dword ptr [rip + Apple_Y ]
add r8d, r9d
sub r8d, ecx
mov eax, r8d
add rsp, 8
ret 
add rsp, 8
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


.section .data
Banana_Y:
.long 2
Apple_X:
.long 2
Apple_Y:
.long 3
