

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
add:
push ebp
mov ebp, esp
sub esp, 8
mov eax , [ebp+8]
mov [add.b], eax 
mov ebx , [ebp+12]
mov [add.a], ebx 
mov ecx , dword [add.a]
add ebx , eax 
mov [add.a], ebx 
mov esp, ebp
pop ebp
ret

main:
push ebp
mov ebp, esp
sub esp, 0
mov eax , dword [std.add]
mov ecx , dword [ret]


[section .data]
return dd 0
false dd 0
true dd 1
Math.history times 256 dd 0
Math.i dd 0
add.b dd 0
add.a dd 0
a dd 1
b dd 2
std.i dd 0
std.history times 256 dd 0
