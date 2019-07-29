

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
banana:
mov eax , dword [a]
mov [d] , eax 
ret

main:
call banana
ret



[section .data]
a dd 23
b dd 25
c dd 1
d dd 2
