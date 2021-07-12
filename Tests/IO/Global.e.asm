.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
mov ecx, dword ptr [rip + a ]
add ecx, dword ptr [rip + b ]
mov eax, ecx
ret 
ret 


_Z4mainv:
jmp Return_Here_76
Return_Here_76:
mov eax, 1
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
