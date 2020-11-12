main:
mov r8, [rdx + 2 * 4 ]
mov rdx, [rcx + r8 * 8 ]
mov ecx, [rdx + 1 * 4 ]
mov eax, ecx
ret 
ret 


