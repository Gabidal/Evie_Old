.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
mov ecx, 0
cmp ecx, 100
jge while0_END
while0:
add ecx, 1
cmp ecx, 100
jge while0_END
jmp while0
while0_END:
if1:
cmp ecx, 100
jne if1_END
mov ecx, 10
if1_END:
if2:
cmp ecx, 100
jne else3
mov ecx, 100
jmp else3_END
if2_END:
else3:
cmp ecx, 10
jne else3_END
mov ecx, 100
else3_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while4_END
while4:
mov ecx, 1
cmp ecx, 2
jge while4_END
jmp while4
while4_END:
mov eax, 0
ret 
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


.section .data
