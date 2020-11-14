main:
mov r9d, 0
cmp r9d, r8d
jg while0_END
while0:
mov r10d, [rdx + r9 * 4 ]
lea r11, [rcx + r9 * 4 ]
mov [r11 ], r10d
add r9d, 1
cmp r9d, r8d
jg while0_END
jmp while0
while0_END:
ret 


