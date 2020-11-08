main:
mov rcx, [() ]
mov rdx, [rcx ]
mov [rdx ], 3
mov [() ], 0
mov rcx, [() ]
mov rdx, [rcx ]
mov ecx, [rdx ]
cmp [() ], ecx
jg while0_END
while0:
mov rax, 1
ret 
mov edx, [() ]
add [() ], 1
mov rcx, [() ]
mov rdx, [rcx ]
mov ecx, [rdx ]
cmp [() ], ecx
jg while0_END
jmp while0
while0_END:
mov rax, [() ]
ret 
ret 


