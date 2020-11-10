main:
mov rdx, [rcx ]
mov r8, [rdx ]
mov [r8 ], 3
mov [() ], 0
mov rdx, [rcx ]
mov r8, [rdx ]
mov ecx, [r8 ]
cmp [() ], ecx
jg while0_END
while0:
mov eax, 1
ret 
mov edx, [() ]
add [() ], 1
mov rdx, [rcx ]
mov r8, [rdx ]
mov ecx, [r8 ]
cmp [() ], ecx
jg while0_END
jmp while0
while0_END:
if1:
mov rdx, [rcx ]
mov r8, [rdx ]
mov ecx, [r8 ]
cmp ecx, 3
jne else2
mov eax, 2
ret 
jmp else2_END
if1_END:
else2:
mov rdx, [rcx ]
mov r8, [rdx ]
mov ecx, [r8 ]
cmp ecx, 4
jne else2_END
mov eax, 3
ret 
else2_END:
mov rdx, [rcx ]
mov r8, [rdx ]
mov ecx, [r8 ]
mov eax, ecx
ret 
ret 


