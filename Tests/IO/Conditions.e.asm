.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
mov ecx, 0
cmp ecx, 100
jge while_9_END
while_9:
add ecx, 1
cmp ecx, 100
jge while_9_END
jmp while_9
while_9_END:
if_10:
cmp ecx, 100
jne if_10_END
mov ecx, 10
if_10_END:
if_11:
cmp ecx, 100
jne else_12
mov ecx, 100
jmp else_12_END
if_11_END:
else_12:
cmp ecx, 10
jne else_12_END
mov ecx, 100
else_12_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while_13_END
while_13:
mov ecx, 1
cmp ecx, 2
jge while_13_END
jmp while_13
while_13_END:
mov eax, 0
ret 
ret 


_Z4mainv:
mov ecx, 0
cmp ecx, 100
jge while_14_END
while_14:
add ecx, 1
cmp ecx, 100
jge while_14_END
jmp while_14
while_14_END:
if_15:
cmp ecx, 100
jne if_15_END
mov ecx, 10
if_15_END:
if_16:
cmp ecx, 100
jne else_17
mov ecx, 100
jmp else_17_END
if_16_END:
else_17:
cmp ecx, 10
jne else_17_END
mov ecx, 100
else_17_END:
jmp Return_Here_27
mov ecx, 1
cmp ecx, 2
jge while_18_END
while_18:
mov ecx, 1
cmp ecx, 2
jge while_18_END
jmp while_18
while_18_END:
jmp Return_Here_27
Return_Here_27:
mov eax, 1
ret 
ret 


.section .data
