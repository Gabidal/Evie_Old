_main: 
push ebp 
mov ebp , esp 
sub esp , dword 36
mov dword [ebp - 28], dword 2
mov eax , dword 0
leave 
ret
 
_mainEND: 
