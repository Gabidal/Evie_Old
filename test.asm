

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
size:
ret

at:
 mov ebx , dword [at_i]
 mov esi, ebx 
 mov return, dword buffer[esi]
ret

set:
 pop ecx 
 mov [set_val], ecx 
 mov esi, dword [set_i]
 lea esi, buffer[esi]
 mov eax , dword [set_val]
 mov [esi], eax 
ret

main:
 mov ebx , 1
 push ebx 
 mov ecx , 3
 push ecx 
 call set
ret



[section .data]
buffer times 256 dd 0
return dd 0
self dd 0
 set_val dd 0 
