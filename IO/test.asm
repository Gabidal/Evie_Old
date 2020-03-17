global _start
_start: 
__start: 
push ebp 
mov ebp , esp 
mov eax , dword 1
mov dword [ebp  - 4], eax 
mov ebx , dword [ebp  - 4]
lea ebx , dword [ebx  + 0 * 4]
push ebx 
call main
sub esp , dword 4
mov eax , eax 
leave 
ret
 
global main
main: 
_main: 
push ebp 
mov ebp , esp 
mov eax , dword [ebp  + 8]
leave 
ret
 
