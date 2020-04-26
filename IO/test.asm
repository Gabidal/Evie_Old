export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 24
lea ebx , dword [ebp  - 4]
mov dword [(ebp  - 28) + 0 * 4], dword 1
mov dword [(ebp  - 28) + 1 * 4], dword 2
mov dword [(ebp  - 28) + 3 * 4], dword 3
mov eax , ebx 
leave 
ret
 
