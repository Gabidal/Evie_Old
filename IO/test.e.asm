extern _Z14internal_printPci
S0:
db "Hello World!"
db 0
main:
mov r8, S0
mov rcx, r8
mov rcx, r8
call Size_Of
mov edx, eax
call _Z14internal_printPci
mov eax, dword 0
ret 
ret 


Size_Of:
mov edx, dword 0
mov r8b, byte [rcx + rdx * 1 ]
cmp r8b, byte 0
je while0_END
while0:
add edx, dword 1
mov r8b, byte [rcx + rdx * 1 ]
cmp r8b, byte 0
je while0_END
jmp while0
while0_END:
mov eax, edx
ret 
ret 


