global _start
_start: 
__start: 
call main
mov eax , eax 
ret
 
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 4
mov eax , dword 1
mov dword [ebp  - 4], eax 
lea ebx , dword [ebp  - 4]
push ebx 
call _get
add esp , dword 4
mov eax , eax 
leave 
ret
 
_get: 
push ebp 
mov ebp , esp 
mov ecx , dword [ebp  + 8]
mov eax , dword [ecx  + 0 * 4]
leave 
ret
 
