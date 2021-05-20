.intel_syntax noprefix
.global Start_Test
.global main
.section .text
main:
mov eax, 1
ret 
ret 


Start_Test:
mov eax, 1
ret 
ret 


char:
mov rax, rcx
ret 
ret 


.section .data
