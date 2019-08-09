

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
getFromNAND:
push ebp
mov ebp, esp
sub esp, 8
mov eax , [ebp+8]
mov [getFromNAND.x], eax 
mov ebx , [ebp+12]
mov [getFromNAND.y], ebx 
mov ecx , dword [a]
mov eax , dword [128]
mov ecx , dword [z]
mov edx , dword [getFromNAND.x]
add ecx , edx 
mov [z], ecx 
mov [return] , ecx 
mov esp, ebp
pop ebp
ret

NAND:
push ebp
mov ebp, esp
sub esp, 8
mov ebx , [ebp+8]
mov [NAND.b], ebx 
mov ecx , [ebp+12]
mov [NAND.a], ecx 
mov [return] , ecx 
mov eax , dword [b]
and ecx , eax 
not ecx 
mov [return], ecx 
mov esp, ebp
pop ebp
ret

main:
push ebp
mov ebp, esp
sub esp, 0
push dword [0]
push dword [0]
call getFromNAND
push dword [0]
push dword [1]
call getFromNAND
push dword [1]
push dword [0]
call getFromNAND
mov esp, ebp
pop ebp
ret



[section .data]
return dd 0
NAND1D.NAND times 128 dd 0
getFromNAND.x dd 0
getFromNAND.y dd 0
getFromNANDz dd 0
NAND.b dd 0
NAND.a dd 0
NAND2D.NAND times 128*128*2 dd 0
