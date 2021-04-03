.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Get:
mov ecx, dword ptr [rip + Banana_Y ]
mov eax, ecx
ret 
ret 


Start_Test:
sub rsp, 8
mov ecx, dword ptr [rip + Banana_Y ]
mov r8d, dword ptr [rip + Apple_Y ]
add ecx, r8d
mov eax, ecx
add rsp, 8
ret 
add rsp, 8
ret 


main:
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
