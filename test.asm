

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
main:
push ebp
mov ebp, esp
sub esp, 0
mov eax , dword [std.a]
mov esi, eax 
lea esi, dword std.c[esi * 4]
mov edx , dword [esi]
mov [b], edx 
mov eax , dword [adt.a]
mov esi, eax 
lea esi, adt.c[esi * 4]
mov eax , dword [esi]
mov esp, ebp
pop ebp
ret



[section .data]
return dd 0
Math.a dd 1
Math.b dd 2
Math.c times 23 dd 0
a dd 1
b dd 2
std.c times 23 dd 0
std.b dd 0
std.a dd 0
adt.c times 23 dd 0
adt.b dd 0
adt.a dd 0
