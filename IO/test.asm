_main: 
push ebp 
mov ebp , esp 
sub esp , dword 4
mov ecx , dword [ebp - 4]
lea ebx , dword [ecx  - 20 * 4]
mov [ebx ], dword 2
mov eax , dword 0
leave 
ret
 
_mainEND: 
