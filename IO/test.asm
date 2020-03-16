global _start
_start: 
__start: 
push ebp 
mov ebp , esp 
mov eax , dword 1.0
mov [ebp  - 4], eax 
push dword [ebp  - 4]
call main
mov eax , dword [ebp  - 4]
leave 
ret
 
global main
main: 
_main: 
push ebp 
mov ebp , esp 
mov ebx , dword [ebp  + 8]
mov ecx , dword 0.0
mov ebx , [ebx  + ecx  * 4]
mov [ebp  - 4], ebx 
mov eax , dword [ebp  - 4]
leave 
ret
 
