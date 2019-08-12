

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
mov ecx , dword [y]

add ecx , [x]
mov [z], ecx 

mov eax , dword [x]

sub eax , ecx 
mov [y], ecx 

mov [x] , ecx 

push eax
mov eax, ecx 
mul ecx 
pop ecx 
xchg eax, ecx 
mov [x], ecx 

mov [z] , ecx 

push eax
mov eax, dword [x]
div ecx 
mov [z], eax
pop eax

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
banana db "\nbananas\n"
banana.size equ $ - banana

apple db "\napple\n"
apple.size equ $ - apple

