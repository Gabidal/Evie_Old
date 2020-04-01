export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 4
xor eax , eax 
leave 
ret
 
_banana: 
mov al , byte 0
ret
 
