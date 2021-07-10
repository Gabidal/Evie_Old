.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
mov ecx, 0
cmp ecx, 100
jge while_0_END
while_0:
add ecx, 1
cmp ecx, 100
jge while_0_END
jmp while_0
while_0_END:
if_1:
cmp ecx, 100
jne if_1_END
mov ecx, 10
if_1_END:
if_2:
mov r8d, 10
cmp r8d, 100
jne else_3
jmp else_3_END
if_2_END:
else_3:
cmp r8d, 10
jne else_3_END
mov r8d, 100
else_3_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while_4_END
while_4:
mov ecx, 1
cmp ecx, 2
jge while_4_END
jmp while_4
while_4_END:
mov eax, 0
ret 
ret 


main:
mov ecx, 0
cmp ecx, 100
jge while_5_END
while_5:
add ecx, 1
cmp ecx, 100
jge while_5_END
jmp while_5
while_5_END:
if_6:
mov r8d, 100
cmp r8d, 100
jne if_6_END
if_6_END:
if_7:
mov r8d, 10
cmp r8d, 100
jne else_3_8
jmp else_3_8_END
if_7_END:
else_3_8:
cmp ecx, 10
jne else_3_8_END
mov ecx, 100
else_3_8_END:
jmp Return_Here_0
mov ecx, 1
cmp ecx, 2
jge while_9_END
while_9:
mov ecx, 1
cmp ecx, 2
jge while_9_END
jmp while_9
while_9_END:
jmp Return_Here_0
Return_Here_0:
mov eax, 1
ret 
ret 


.section .data
