export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 12
mov eax , dword 0
mov dword [ebp  - 4], eax 
mov ebx , dword [ebp  - 4]
mov dword [ebp  - 8], ebx 
mov eax , dword [ebp  - 8]
leave 
ret
 
