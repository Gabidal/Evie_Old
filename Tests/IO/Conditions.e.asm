.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 0		#i, 0
cmp ecx, 100		#i, 100
jge while_33_END		#while_33_END
while_33:
add ecx, 1		#i, 1
cmp ecx, 100		#i, 100
jge while_33_END		#while_33_END
jmp while_33		#while_33
while_33_END:
if_34:
cmp ecx, 100		#i, 100
jne if_34_END		#if_34_END
mov ecx, 10		#i, 10
if_34_END:
if_35:
cmp ecx, 100		#i, 100
jne else_36		#else_36
mov ecx, 100		#i, 100
jmp else_36_END		#else_36_END
if_35_END:
else_36:
cmp ecx, 10		#i, 10
jne else_36_END		#else_36_END
mov ecx, 100		#i, 100
else_36_END:
mov eax, ecx		#Returning_REG0, i
ret 		#
mov ecx, 1		#REG_11, 1
cmp ecx, 2		#REG_11, 2
jge while_37_END		#while_37_END
while_37:
mov ecx, 1		#REG_12, 1
cmp ecx, 2		#REG_12, 2
jge while_37_END		#while_37_END
jmp while_37		#while_37
while_37_END:
mov eax, 0		#Returning_REG3, 0
ret 		#
ret 		#


_Z4mainv:
mov ecx, 0		#i_84, 0
cmp ecx, 100		#i_84, 100
jge while_38_END		#while_38_END
while_38:
add ecx, 1		#i_84, 1
cmp ecx, 100		#i_84, 100
jge while_38_END		#while_38_END
jmp while_38		#while_38
while_38_END:
if_39:
cmp ecx, 100		#i_84, 100
jne if_39_END		#if_39_END
mov ecx, 10		#i_84, 10
if_39_END:
if_40:
cmp ecx, 100		#i_84, 100
jne else_41		#else_41
mov ecx, 100		#i_84, 100
jmp else_41_END		#else_41_END
if_40_END:
else_41:
cmp ecx, 10		#i_84, 10
jne else_41_END		#else_41_END
mov ecx, 100		#i_84, 100
else_41_END:
jmp Return_Here_118		#Return_Here_118
mov ecx, 1		#REG_10, 1
cmp ecx, 2		#REG_10, 2
jge while_42_END		#while_42_END
while_42:
mov ecx, 1		#REG_11, 1
cmp ecx, 2		#REG_11, 2
jge while_42_END		#while_42_END
jmp while_42		#while_42
while_42_END:
jmp Return_Here_118		#Return_Here_118
Return_Here_118:
mov eax, 1		#Returning_REG2, 1
ret 		#
ret 		#


.section .data		#.data
