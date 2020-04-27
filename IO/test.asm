export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 28
lea ebx , dword [ebp  - 4]
mov [ebp  - 28], dword 0
mov ecx , ebx 
mov dword [ecx  + ebp  - 28 * 4], dword 1
mov dword [ecx  + 0 * 4], dword 2
mov dword [ecx  + 3 * 4], dword 3
mov eax , ebx 
leave 
ret
 
