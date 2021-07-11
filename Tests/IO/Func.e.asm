.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text
_Z4mainv:
lea rcx, qword ptr [rip + foo ]
mov rcx, rcx
jmp Return_Here_15
Return_Here_15:
mov eax, 1
ret 
ret 


foo:
mov eax, 5
ret 
ret 


_Z10Start_Testv:
lea rcx, qword ptr [rip + foo ]
mov rcx, rcx
call rcx
mov eax, eax
ret 
ret 


.section .data
