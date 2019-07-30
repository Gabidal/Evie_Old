

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
banana:
mov eax , dword [e]
mov [d] , eax 
ret

mov ecx , dword [a]
mov esi, ecx 
mov b, dword abc[esi]
mov esi, dword [a]
lea esi, abc[esi]
mov eax , dword [b]
mov [esi], eax 
main:
call banana
ret



[section .data]
d dd 1
e dd 2
a dd 23
b dd 25
c dd 1
abc times 128 dd 0
