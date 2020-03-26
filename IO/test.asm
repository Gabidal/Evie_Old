export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 4
mov eax , dword [a]
leave 
ret
 
