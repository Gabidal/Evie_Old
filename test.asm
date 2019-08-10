

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
mov eax , dword [a]

push eax
mov eax, dword [a]
mov ecx , dword [a]
mul ecx 
mov [a], eax
pop eax

mov edx , dword [b]

push eax
mov eax, ecx 
div edx 
pop ecx 
xchg eax, ecx 
mov [a], ecx 

mov [a] , edx 

mov ecx , dword [c]
add edx , ecx 
mov [a], edx 

mov [a] , ecx 

sub ecx , ecx 
mov [a], ecx 

mov esp, ebp
pop ebp
ret



section .data
return dd 0
a dd 0
b dd 2
c dd 3
