main:
push rdi
push rbx
mov r10d, 0
cmp r10d, r8d
jg while0_END
while0:
mov ebx, [r9 + r10 * 4 ]
mov edi, [rdx + r10 * 4 ]
add edi, ebx
lea r11, [rcx + r10 * 4 ]
mov [r11 ], edi
add r10d, 1
cmp r10d, r8d
jg while0_END
jmp while0
while0_END:
pop rdi
pop rbx
ret 


