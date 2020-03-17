global _start
_start: 
__start: 
push ebp 
mov ebp , esp 
mov al , byte 1
movsx eax , al 
mov eax , eax 
mov [ebp  - 4], eax 
push dword [ebp  - 4]
call main
sub esp , dword 4
mov eax , dword [ebp  - 4]
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
 
