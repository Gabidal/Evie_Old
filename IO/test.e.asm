.intel_syntax noprefix
.global main
.section .text
main:
mov rcx, qword ptr [rcx + 4 ]
lea rcx, qword ptr [rcx + 1 * 4 ]
mov eax, dword ptr [rcx ]
ret 
ret 


.section .data
