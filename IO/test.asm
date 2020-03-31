export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 4
xor eax , eax 
mov dword [ebp  - 4], eax 
mov eax , dword [ebp  - 4]
leave 
ret
 
_banana: 
mov al , byte 0
ret
 
