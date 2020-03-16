global _start
_start: 
__start: 
push ebp 
mov ebp , esp 
mov eax , dword 1.0
mov [ebp  - 4], eax 
push dword [ebp  - 4]
call _main
mov eax , dword [ebp  - 4]
leave 
ret
 
global main
main: 
_main: 
push ebp 
mov ebp , esp 
mov ebx , dword 0.0
mov ecx , [(ebp  + 8) + ebx  * 4]
mov [ebp  - 4], ecx 
mov eax , dword [ebp  - 4]
leave 
ret
 
