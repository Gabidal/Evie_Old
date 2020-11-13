main:
mov [() ], 0
jg while0_END
while0:
mov r9d, [rdx + r8 * 4 ]
mov r10, [() ]
lea r11, [rcx + r10 * 4 ]
mov [r11 ], r9d
mov r9d, [() ]
add [() ], 1
jg while0_END
jmp while0
while0_END:
ret 


