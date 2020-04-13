_main: 
push ebp 
mov ebp , esp 
sub esp , dword 8
mov eax , dword 0
mov dword [ebp  - 4], eax 
mov eax , dword [(ebp  - 4) + 0 * 4]
mov dword [ebp  - 8], eax 
