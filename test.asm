

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
get:
 push ebp
 mov ebp, esp
 sub esp, 12
 mov eax , [ebp+8]
 mov [get_c], eax 
 mov ebx , [ebp+12]
 mov [get_b], ebx 
 mov ecx , [ebp+16]
 mov [get_a], ecx 
 mov esi, ecx 
 lea esi, dword buffer[esi * 4]
 mov eax , dword [esi]
 mov [return], eax 
 mov esp, ebp
 pop ebp
ret

main:
 push ebp
 mov ebp, esp
 sub esp, 0
 mov ecx , dword [a]
 push ecx 
 mov edx , dword [a]
 push edx 
 mov eax , dword [a]
 push eax 
 call get
 mov [a], eax 
 mov esp, ebp
 pop ebp
ret



[section .data]
buffer times 256 dd 0
return dd 0
get_c dd 0
get_b dd 0
get_a dd 0
a dd 0
