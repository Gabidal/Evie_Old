

section .text
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

section .code
gout:
push ebp
mov ebp, esp
sub esp, 8
;size is now a variable.
mov eax , [ebp+8]
mov [gout.size], eax 
;name is now a variable.
mov ebx , [ebp+12]
mov [gout.name], ebx 
mov eax, 4
mov ebx, 1
mov ecx, [gout.name]
mov edx, [gout.size]
int 80h
mov esp, ebp
pop ebp
ret

main:
push ebp
mov ebp, esp
sub esp, 0
lea esi, [banana]
push esi
lea esi, [banana.size]
push esi
call gout
lea edi, [banana]
lea esi, [apple]
push ecx
mov ecx, apple.size
repz movsb 
lea esi, [apple]
push esi
lea esi, [apple.size]
push esi
call gout
mov esp, ebp
pop ebp
ret



section .data
return dd 0
gout.size dd 0
gout.name dd 0
x dd 1
y dd 1
z dd 0
banana db 'bananas',10, 0
banana.size equ $ - banana

apple db 'apple',10, 0
apple.size equ $ - apple

