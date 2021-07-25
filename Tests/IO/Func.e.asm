.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text		#.text
_Z4mainv:
lea rcx, qword ptr [rip + foo ]		#foo_REG0, .RIP_foo
mov rcx, rcx		#fuz_80, foo_REG0
jmp Return_Here_115		#Return_Here_115
Return_Here_115:
mov eax, 1		#Returning_REG1, 1
ret 		#
ret 		#


foo:
mov eax, 5		#Returning_REG0, 5
ret 		#
ret 		#


_Z10Start_Testv:
lea rcx, qword ptr [rip + foo ]		#foo_REG0, .RIP_foo
mov rcx, rcx		#fuz, foo_REG0
call rcx
mov eax, eax		#Returning_REG2, RetREG_1
ret 		#
ret 		#


.section .data		#.data
