

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
mov ecx , dword [a]
lea esi, d.bit[4*(1*12*12+2*12+3)]
mov [esi], ecx 
mov esi, 1*12*12+2*12+3
mov ebx , dword [esi]
mov [b], ebx 
mov esp, ebp
pop ebp
ret



[section .data]
return dd 0
Bit.bit times 8 dd 0
Word.bit times 8*2*2 dd 0
Double.bit times 8*2*4 dd 0
a dd 989
b dd 0
d.bit times 8*2*6 dd 0
