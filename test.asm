

section .text
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

section .code
main:
push ebp
mov ebp, esp
sub esp, 0
mov eax , dword [a]

push eax
mov eax, [main.b]
mov ecx , dword [a]
div ecx 
mov [a], eax
pop eax

mov esp, ebp
pop ebp
ret



section .data
return dd 0
a dd 1
main.b dd 2
