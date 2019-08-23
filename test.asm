

section .text

global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

section .code
 banana:
push ebp
mov ebp, esp
sub esp, 1
;c is now Variable.
mov eax , [ebp+8]
mov [ banana.c], eax 
push banana.b
mov ebx , dword [banana.c]
pop esi 
mov [esi ], ebx 
push banana.c
mov ecx , dword [a]
pop edi 
mov [edi ], ecx 
mov esp, ebp
pop ebp
ret

 main:
push ebp
mov ebp, esp
sub esp, 0
mov esp, ebp
pop ebp
ret



section .data

a dd 0
 banana.c dd 0
banana.b dd 1


section .bss

