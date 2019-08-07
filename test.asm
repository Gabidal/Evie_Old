

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
Math.NAND:
push ebp
mov ebp, esp
sub esp, 8
mov eax , [ebp+8]
mov [Math.NAND.b], eax 
mov ebx , [ebp+12]
mov [Math.NAND.a], ebx 
mov [return] , ebx 
and ebx , eax 
not ebx 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

Math.OR:
push ebp
mov ebp, esp
sub esp, 8
mov edx , [ebp+8]
mov [Math.OR.b], edx 
mov eax , [ebp+12]
mov [Math.OR.a], eax 
mov [return] , ebx 
or ebx , eax 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

Math.XOR:
push ebp
mov ebp, esp
sub esp, 8
mov ecx , [ebp+8]
mov [Math.XOR.b], ecx 
mov edx , [ebp+12]
mov [Math.XOR.a], edx 
mov [return] , ebx 
xor ebx , eax 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

Math.NOR:
push ebp
mov ebp, esp
sub esp, 8
mov ebx , [ebp+8]
mov [Math.NOR.b], ebx 
mov ecx , [ebp+12]
mov [Math.NOR.a], ecx 
mov [return] , ebx 
or ebx , eax 
not ebx 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

Math.AND:
push ebp
mov ebp, esp
sub esp, 8
mov eax , [ebp+8]
mov [Math.AND.b], eax 
mov ebx , [ebp+12]
mov [Math.AND.a], ebx 
mov [return] , ebx 
and ebx , eax 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

float.make:
push ebp
mov ebp, esp
sub esp, 0
mov edx , [ebp+8]
mov [float.make.val], edx 
mov eax , [ebp+12]
mov [float.make.name], eax 
mov esp, ebp
pop ebp
ret

main:
push ebp
mov ebp, esp
sub esp, 0
mov ebx , dword [std.c]
mov [a] , ebx 
mov esp, ebp
pop ebp
ret



[section .data]
return dd 0
false dd 0
true dd 1
Math.c dd 123
Math.bits times 123 dd 0
Math.NAND.b dd 0
Math.NAND.a dd 0
Math.OR.b dd 0
Math.OR.a dd 0
Math.XOR.b dd 0
Math.XOR.a dd 0
Math.NOR.b dd 0
Math.NOR.a dd 0
Math.AND.b dd 0
Math.AND.a dd 0
float.make.val dd 0
float.make.name dd 0
float.make%name dd %val
a dd 0
b dd 1
std.c dd 0
