

section .text

global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

 banana:
push ebp
mov ebp, esp
sub esp, 3
;a is now Variable.
mov eax , [ebp+8]
mov [ banana.a], eax 
;b is now Variable.
mov ebx , [ebp+12]
mov [ banana.b], ebx 
;c is now Variable.
mov ecx , [ebp+16]
mov [ banana.c], ecx 
push dword [banana.a]
mov edx , dword [banana.c]
mov eax , dword [banana.b]
add eax , edx 

pop esi 
mov [esi ], eax 
mov esp, ebp
pop ebp
ret

 main:
push ebp
mov ebp, esp
sub esp, 0
push dword [c]
push dword [b]
push dword [a]
call banana
mov esp, ebp
pop ebp
ret



section .data

a dd 1
b dd 2
c dd 3
 banana.a dd 0
 banana.b dd 0
 banana.c dd 0


section .bss

