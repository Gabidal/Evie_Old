

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
lenght:
 pop edi
 mov [_Layer_0], edi 
 pop eax 
 mov [ptr], eax 
 mov edi, dword [_Layer_0]
 push edi
ret

from:
 pop edi
 mov [_Layer_1], edi 
 pop ebx 
 mov [at_i], ebx 
 mov esi, 5
 mov eax , dword buffer[esi*4]
 mov [return], eax 
 mov edi, dword [_Layer_1]
 push edi
ret

set:
 pop edi
 mov [_Layer_2], edi 
 pop ebx 
 mov [set_i], ebx 
 pop ecx 
 mov [set_val], ecx 
 mov esi, dword [set_i]
 lea esi, buffer[esi*4]
 mov eax , 5
 mov [esi], eax 
 mov edi, dword [_Layer_2]
 push edi
ret

main:
 pop edi
 mov [_Layer_3], edi 
 mov ecx , dword [a]
 mov esi, ecx 
 mov edx , dword b[esi*4]
 mov [c], edx 
 mov eax , 3
 mov ebx , 1
 push eax 
 push ebx 
 call set
 mov edi, dword [_Layer_3]
 push edi
ret



[section .data]
buffer times 256 dd 0
return dd 0
self dd 0
_Layer_0 dd 0
 ptr dd 0 
_Layer_1 dd 0
 at_i dd 0 
_Layer_2 dd 0
 set_i dd 0 
 set_val dd 0 
a dd 1
b dd 0
c dd 0
_Layer_3 dd 0
