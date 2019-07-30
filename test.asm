

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
at:
 pop eax 
 mov [i], eax 
 mov ecx , dword [i]
 mov esi, ecx 
 mov return, dword buffer[esi]
ret

set:
 pop edx 
 mov [val], edx 
 pop eax 
 mov [i], eax 
 mov esi, dword [i]
 lea esi, buffer[esi]
 mov ecx , dword [val]
 mov [esi], ecx 
ret

main:
 mov edx , 1
 push edx 
 mov eax , 3
 push eax 
 call set
ret



[section .data]
buffer times 256 dd 0
return dd 0
 at dd 0 
 set dd 0 
 set dd 0 
