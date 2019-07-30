

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
banana:
mov eax , dword [f]
mov [d] , eax 
ret

ret

main:
call banana
ret



[section .data]
d dd 34
e dd 65
f dd 98
a dd 23
b dd 25
c dd 1
