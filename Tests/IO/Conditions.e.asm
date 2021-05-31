.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
mov ecx, 0
cmp ecx, 100
jge while48_END
while48:
add ecx, 1
cmp ecx, 100
jge while48_END
jmp while48
while48_END:
if49:
cmp ecx, 100
jne if49_END
mov ecx, 10
if49_END:
if50:
cmp ecx, 100
jne else51
mov ecx, 100
jmp else51_END
if50_END:
else51:
cmp ecx, 10
jne else51_END
mov ecx, 100
else51_END:
mov eax, ecx
ret 
mov ecx, 1
cmp ecx, 2
jge while52_END
while52:
mov ecx, 1
cmp ecx, 2
jge while52_END
jmp while52
while52_END:
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


____Deallocate_BYTE_POINTER_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


.section .data
