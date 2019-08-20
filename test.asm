

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


section .data

abc.size equ $ - abc
efg.size equ $ - efg
a dd 2


section .bss

abc resd 256
efg resd 34
