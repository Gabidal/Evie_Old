.intel_syntax noprefix
.global main
.global Start_Test
Start_Test:
mov ecx, 0
cmp ecx, 100
jge while5_END
while5:
mov r8d, ecx
add ecx, 1
cmp ecx, 100
jge while5_END
jmp while5
while5_END:
if6:
cmp ecx, 100
jne if6_END
mov ecx, 10
if6_END:
if7:
cmp ecx, 100
jne else8
mov ecx, 100
jmp else8_END
if7_END:
else8:
cmp ecx, 10
jne else8_END
mov ecx, 100
else8_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while9_END
while9:
mov ecx, 1
cmp ecx, 2
jge while9_END
jmp while9
while9_END:
mov eax, 0
ret 
ret 


main:
mov eax, 1
ret 
ret 


