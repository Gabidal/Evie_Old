export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 4
mov eax , dword 0
mov dword [ebp  - 4], eax 
mov eax , dword [ebp  - 4]
leave 
ret
 
