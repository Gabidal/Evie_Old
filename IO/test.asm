_main: 
push ebp 
mov ebp , esp 
sub esp , dword 4
mov eax , dword 1
mov dword [ebp  - 4], eax 
