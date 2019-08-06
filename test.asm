

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
math.NAND:
push ebp
mov ebp, esp
sub esp, 8
mov eax , [ebp+8]
mov [math.NAND.b], eax 
mov ebx , [ebp+12]
mov [math.NAND.a], ebx 
mov [math.NANDreturn] , ebx 
and ebx , eax 
not ebx 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

math.OR:
push ebp
mov ebp, esp
sub esp, 8
mov edx , [ebp+8]
mov [math.OR.b], edx 
mov eax , [ebp+12]
mov [math.OR.a], eax 
mov [math.ORreturn] , ebx 
or ebx , eax 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

math.XOR:
push ebp
mov ebp, esp
sub esp, 8
mov ecx , [ebp+8]
mov [math.XOR.b], ecx 
mov edx , [ebp+12]
mov [math.XOR.a], edx 
mov [math.XORreturn] , ebx 
xor ebx , eax 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

math.NOR:
push ebp
mov ebp, esp
sub esp, 8
mov ebx , [ebp+8]
mov [math.NOR.b], ebx 
mov ecx , [ebp+12]
mov [math.NOR.a], ecx 
mov [math.NORreturn] , ebx 
or ebx , eax 
not ebx 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

math.AND:
push ebp
mov ebp, esp
sub esp, 8
mov eax , [ebp+8]
mov [math.AND.b], eax 
mov ebx , [ebp+12]
mov [math.AND.a], ebx 
mov [math.ANDreturn] , ebx 
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
push ebx 
push eax 
call math.NAND
mov ecx , dword [return]
mov [a], ecx 
mov esp, ebp
pop ebp
ret



[section .data]
  return dd 0
  false dd 0
  true dd 1
math.NAND.b dd 0
math.NAND.a dd 0
math.OR.b dd 0
math.OR.a dd 0
math.XOR.b dd 0
math.XOR.a dd 0
math.NOR.b dd 0
math.NOR.a dd 0
math.AND.b dd 0
math.AND.a dd 0
float.make.val dd 0
float.make.name dd 0
float.make%name dd %val
  a dd 0
  b dd 1
