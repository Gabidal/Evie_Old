

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
mov ecx , dword [false]
cmp ebx , ecx 
 jne else11
 cmp eax , ecx 
  jne else22
  mov edx , dword [true]
  mov eax , edx 
  mov [return] , eax 
  jmp end22
  else22: 
  mov [return] , edx 
  end22: 
 jmp end11
 else11: 
 cmp eax , edx 
  jne else23
  mov [return] , ecx 
  jmp end23
  else23: 
  mov [return] , edx 
  end23: 
  end23: 
mov esp, ebp
pop ebp
ret

main:
push ebp
mov ebp, esp
sub esp, 0
mov ebx , dword [a]
push ebx 
mov ecx , dword [a]
push ecx 
call NAND
mov [a], edx 
mov esp, ebp
pop ebp
ret



[section .data]
return dd 0
false dd 0
true dd 1
NAND_b dd 0
NAND_a dd 0
a dd 0
