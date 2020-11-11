main:
mov r8, [rcx + 1 * 8 ]
mov r9, [r8 + 2 * 8 ]
mov [r9 ], 1
mov r10, [rdx ]
mov rdx, [r10 ]
mov r10, [rdx ]
mov r8, [rcx + r10 * 8 ]
mov ecx, [r8 + 2 * 8 ]
mov eax, ecx
ret 
ret 


