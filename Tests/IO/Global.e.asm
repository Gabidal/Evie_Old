.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, dword ptr [rip + a ]		#REG_a0, .RIP_a
add ecx, dword ptr [rip + b ]		#REG_a0, .RIP_b
mov eax, ecx		#Returning_REG1, REG_a0
ret 		#
ret 		#


_Z4mainv:
jmp Return_Here_154		#Return_Here_154
Return_Here_154:
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


.section .data		#.data
a:
.long 1		#1
b:
.long 3		#3
GLOBAL_SCOPE_a:
.long 0		#0
GLOBAL_SCOPE_b:
.long 0		#0
