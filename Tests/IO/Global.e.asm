.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
mov ecx, dword ptr [rip + a ]
add ecx, dword ptr [rip + b ]
mov eax, ecx
ret 
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


char:
mov rax, rcx
ret 
ret 


.section .data
a:
.long 1
b:
.long 3
GLOBAL_SCOPE_a:
.long 0
GLOBAL_SCOPE_b:
.long 0
