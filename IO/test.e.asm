main:
mov [() ], 0
jg while0_END
while0:
mov r8, [() ]
mov r8d, [rdx + r8 * 4 ]
mov r8, [() ]
mov rdx, [rcx + r8 * 4 ]
mov [rdx ], r8d
mov ecx, [() ]
add [() ], 1
jg while0_END
jmp while0
while0_END:
ret 


