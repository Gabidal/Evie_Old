.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
mov ecx, 0
cmp ecx, 100
jge while7_END
while7:
mov r8d, ecx
add ecx, 1
cmp ecx, 100
jge while7_END
jmp while7
while7_END:
if8:
cmp ecx, 100
jne if8_END
mov ecx, 10
if8_END:
if9:
cmp ecx, 100
jne else10
mov ecx, 100
jmp else10_END
if9_END:
else10:
cmp ecx, 10
jne else10_END
mov ecx, 100
else10_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while11_END
while11:
mov ecx, 1
cmp ecx, 2
jge while11_END
jmp while11
while11_END:
mov eax, 0
ret 
ret 


main:
mov eax, 1
ret 
ret 


.section .data
