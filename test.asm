

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
banana:
mov eax , dword [a]
mov [a], eax 
push eax
mov eax, eax 
xor edx, edx
mul eax 
mov [a], eax
pop eax
mov ebx , dword [b]
mov [b], ebx 
push eax
mov eax, ebx 
xor edx, edx
mul ebx 
mov [b], eax
pop eax
ret

apple:
mov ecx , dword [b]
mov [a], ecx 
mov edx , dword [a]
mov [b], edx 
mov eax , dword [a]
mov [c], eax 
add eax , ebx 
mov [c], eax 
ret

main:
call banana
call apple
ret



[section .data]
a dd 23
b dd 25
c dd 0
