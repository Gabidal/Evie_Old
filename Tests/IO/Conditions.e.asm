.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 0		#i, 0
cmp ecx, 100		#i, 100
jge while_34_END		#while_34_END
while_34:
add ecx, 1		#i, 1
cmp ecx, 100		#i, 100
jge while_34_END		#while_34_END
jmp while_34		#while_34
while_34_END:
if_35:
cmp ecx, 100		#i, 100
jne if_35_END		#if_35_END
mov ecx, 10		#i, 10
if_35_END:
if_36:
cmp ecx, 100		#i, 100
jne else_37		#else_37
mov ecx, 100		#i, 100
jmp else_37_END		#else_37_END
if_36_END:
else_37:
cmp ecx, 10		#i, 10
jne else_37_END		#else_37_END
mov ecx, 100		#i, 100
else_37_END:
mov eax, ecx		#Returning_REG0, i
ret 		#
mov ecx, 1		#REG_11, 1
cmp ecx, 2		#REG_11, 2
jge while_38_END		#while_38_END
while_38:
mov ecx, 1		#REG_12, 1
cmp ecx, 2		#REG_12, 2
jge while_38_END		#while_38_END
jmp while_38		#while_38
while_38_END:
mov eax, 0		#Returning_REG3, 0
ret 		#
ret 		#


_Z4mainv:
mov ecx, 0		#i_90, 0
cmp ecx, 100		#i_90, 100
jge while_39_END		#while_39_END
while_39:
add ecx, 1		#i_90, 1
cmp ecx, 100		#i_90, 100
jge while_39_END		#while_39_END
jmp while_39		#while_39
while_39_END:
if_40:
cmp ecx, 100		#i_90, 100
jne if_40_END		#if_40_END
mov ecx, 10		#i_90, 10
if_40_END:
if_41:
cmp ecx, 100		#i_90, 100
jne else_42		#else_42
mov ecx, 100		#i_90, 100
jmp else_42_END		#else_42_END
if_41_END:
else_42:
cmp ecx, 10		#i_90, 10
jne else_42_END		#else_42_END
mov ecx, 100		#i_90, 100
else_42_END:
jmp Return_Here_127		#Return_Here_127
mov ecx, 1		#REG_10, 1
cmp ecx, 2		#REG_10, 2
jge while_43_END		#while_43_END
while_43:
mov ecx, 1		#REG_11, 1
cmp ecx, 2		#REG_11, 2
jge while_43_END		#while_43_END
jmp while_43		#while_43
while_43_END:
jmp Return_Here_127		#Return_Here_127
Return_Here_127:
mov eax, 1		#Returning_REG2, 1
ret 		#
ret 		#


.section .data		#.data
