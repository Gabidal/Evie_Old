

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
sub esp, 1
; is now Variable.
mov edx , [ebp+8]
mov [ main.], edx 
push main.
push dword [d]
call banana
push d
push d
push d
push main.
mov esp, ebp
pop ebp
ret

push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.
push main.


section .data

 d dd 12
 bananaa dd 0
 bananab dd 0
 bananac dd 0
 main dd 0


section .bss

