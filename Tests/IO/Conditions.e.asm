.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
mov ecx, 0
cmp ecx, 100
jge while_10_END
while_10:
add ecx, 1
cmp ecx, 100
jge while_10_END
jmp while_10
while_10_END:
if_11:
cmp ecx, 100
jne if_11_END
mov ecx, 10
if_11_END:
if_12:
cmp ecx, 100
jne else_13
mov ecx, 100
jmp else_13_END
if_12_END:
else_13:
cmp ecx, 10
jne else_13_END
mov ecx, 100
else_13_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while_14_END
while_14:
mov ecx, 1
cmp ecx, 2
jge while_14_END
jmp while_14
while_14_END:
mov eax, 0
ret 
ret 


_Z4mainv:
mov ecx, 0
cmp ecx, 100
jge while_15_END
while_15:
add ecx, 1
cmp ecx, 100
jge while_15_END
jmp while_15
while_15_END:
if_16:
cmp ecx, 100
jne if_16_END
mov ecx, 10
if_16_END:
if_17:
cmp ecx, 100
jne else_18
mov ecx, 100
jmp else_18_END
if_17_END:
else_18:
cmp ecx, 10
jne else_18_END
mov ecx, 100
else_18_END:
jmp Return_Here_40
mov ecx, 1
cmp ecx, 2
jge while_19_END
while_19:
mov ecx, 1
cmp ecx, 2
jge while_19_END
jmp while_19
while_19_END:
jmp Return_Here_40
Return_Here_40:
mov eax, 1
ret 
ret 


.section .data
