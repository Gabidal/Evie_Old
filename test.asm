

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
push a
mov eax , dword [c]
mov ebx , dword [b]
add ebx , eax 

pop esi 
mov [esi ], ebx 
push b
mov ecx , dword [a]
sub eax , ecx 

pop edi 
mov [edi ], eax 
push c
imul ecx , ebx 

pop esi 
mov [esi ], ecx 
mov esp, ebp
pop ebp
ret



section .data

 a dd 1
 b dd 2
 c dd 3


section .bss

