

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
NAND:
push ebp
mov ebp, esp
sub esp, 8
mov eax , [ebp+8]
mov [NAND_b], eax 
mov ebx , [ebp+12]
mov [NAND_a], ebx 
mov [return] , ebx 
and ebx , eax 
not ebx 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

OR:
push ebp
mov ebp, esp
sub esp, 8
mov edx , [ebp+8]
mov [OR_b], edx 
mov eax , [ebp+12]
mov [OR_a], eax 
mov [return] , eax 
or eax , edx 
mov [return], eax 
mov esp, ebp
pop ebp
ret

XOR:
push ebp
mov ebp, esp
sub esp, 8
mov ecx , [ebp+8]
mov [XOR_b], ecx 
mov edx , [ebp+12]
mov [XOR_a], edx 
mov [return] , edx 
xor edx , ecx 
mov [return], edx 
mov esp, ebp
pop ebp
ret

NOR:
push ebp
mov ebp, esp
sub esp, 8
mov ebx , [ebp+8]
mov [NOR_b], ebx 
mov ecx , [ebp+12]
mov [NOR_a], ecx 
mov [return] , ecx 
or ecx , ebx 
not ecx 
mov [return], ecx 
mov esp, ebp
pop ebp
ret

AND:
push ebp
mov ebp, esp
sub esp, 8
mov eax , [ebp+8]
mov [AND_b], eax 
mov ebx , [ebp+12]
mov [AND_a], ebx 
mov [return] , ebx 
and ebx , eax 
mov [return], ebx 
mov esp, ebp
pop ebp
ret

main:
push ebp
mov ebp, esp
sub esp, 0
push dword [a]
push dword [b]
call NAND
mov ecx , dword [return]
mov [a], ecx 
push dword [a]
push dword [b]
call OR
mov [b], ecx 


[section .data]
return dd 0
false dd 0
true dd 1
NAND_b dd 0
NAND_a dd 0
OR_b dd 0
OR_a dd 0
XOR_b dd 0
XOR_a dd 0
NOR_b dd 0
NOR_a dd 0
AND_b dd 0
AND_a dd 0
a dd 0
b dd 1
