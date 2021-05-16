.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
mov ecx, 0
cmp ecx, 100
jge while14_END
while14:
add ecx, 1
cmp ecx, 100
jge while14_END
jmp while14
while14_END:
if15:
cmp ecx, 100
jne if15_END
mov ecx, 10
if15_END:
if16:
cmp ecx, 100
jne else17
mov ecx, 100
jmp else17_END
if16_END:
else17:
cmp ecx, 10
jne else17_END
mov ecx, 100
else17_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while18_END
while18:
mov ecx, 1
cmp ecx, 2
jge while18_END
jmp while18
while18_END:
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
