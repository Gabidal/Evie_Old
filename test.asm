

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
size:
 pop eax 
 mov [ptr], eax 
ret

at:
 pop ebx 
 mov [at_i], ebx 
 mov edx , dword [at_i]
 mov esi, edx 
 mov return, dword buffer[esi]
ret

set:
 pop eax 
 mov [set_i], eax 
 pop ebx 
 mov [set_val], ebx 
 mov esi, dword [set_i]
 lea esi, buffer[esi]
 mov edx , dword [set_val]
 mov [esi], edx 
ret

main:
 mov eax , 3
 mov ebx , 1
 push eax 
 push ebx 
 call set
ret



[section .data]
buffer times 256 dd 0
return dd 0
self dd 0
 ptr dd 0 
 at_i dd 0 
 set_i dd 0 
 set_val dd 0 
