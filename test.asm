

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
push banana.c
push banana.a
push banana.b
mov esp, ebp
pop ebp
ret

 main:
push ebp
mov ebp, esp
sub esp, 0
push d
push d
push d
call banana
mov esp, ebp
pop ebp
ret



section .data

 d dd 12
 banana.a dd 0
 banana.b dd 0
 banana.c dd 0


section .bss

