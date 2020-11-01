main:
mov eax, 0
mov eax, 0
cmp eax, eax
jne if0_END
mov eax, 2
mov ecx, 1
add ecx, eax
mov a, ecx
jmp if0_END
if0_END:
ret 


