

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
get:
 pop edi
 mov [_Layer_0], edi 
 pop eax 
 mov [get_i], eax 
 mov ecx , dword [get_i]
 mov esi, ecx 
 mov edx , dword buffer[esi*4]
 mov [return], edx 
 mov edi, dword [_Layer_0]
 push edi
ret

main:
 pop edi
 mov [_Layer_1], edi 
 mov ebx , dword [a]
 push ebx 
 call get
 mov [a], edx 
 mov edi, dword [_Layer_1]
 push edi
ret



[section .data]
buffer times 256 dd 0
return dd 0
_Layer_0 dd 0
 get_i dd 0 
a dd 0
_Layer_1 dd 0
