.intel_syntax noprefix
.global main
.global Start_Test
Start_Test:
mov ecx, 0
cmp ecx, 100
jge while1_END
while1:
mov r8d, ecx
add ecx, 1
cmp ecx, 100
jge while1_END
jmp while1
while1_END:
if2:
cmp ecx, 100
jne if2_END
mov ecx, 10
if2_END:
if3:
cmp ecx, 100
jne else4
mov ecx, 100
jmp else4_END
if3_END:
else4:
cmp ecx, 10
jne else4_END
mov ecx, 100
else4_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while5_END
while5:
mov ecx, 1
cmp ecx, 2
jge while5_END
jmp while5
while5_END:
mov eax, 0
ret 
ret 


main:
mov eax, 1
ret 
ret 


