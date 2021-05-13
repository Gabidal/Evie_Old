.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
mov ecx, 0
cmp ecx, 100
jge while3_END
while3:
add ecx, 1
cmp ecx, 100
jge while3_END
jmp while3
while3_END:
if4:
cmp ecx, 100
jne if4_END
mov ecx, 10
if4_END:
if5:
cmp ecx, 100
jne else6
mov ecx, 100
jmp else6_END
if5_END:
else6:
cmp ecx, 10
jne else6_END
mov ecx, 100
else6_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while7_END
while7:
mov ecx, 1
cmp ecx, 2
jge while7_END
jmp while7
while7_END:
mov eax, 0
ret 
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


char:
mov rax, rcx
ret 
ret 


.section .data
