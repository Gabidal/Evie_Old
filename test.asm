

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
push dword [banana.a]
mov edx , dword [banana.c]
mov eax , dword [banana.b]
add eax , edx 
mov ebx , dword [banana.a]
sub eax , ebx 
pop esi 
mov [esi ], eax 
mov esp, ebp
pop ebp
ret

 main:
push ebp
mov ebp, esp
sub esp, 0
mov edi , dword [d]
lea edi , abc[ edi * 4]
push dword [edi ]
push dword [d]
push dword [d]
call banana
mov esp, ebp
pop ebp
ret



section .data

 d dd 12
 abc.size equ $ -  abc
 banana.a dd 0
 banana.b dd 0
 banana.c dd 0


section .bss

 abc resd 2
