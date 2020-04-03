_banana: 
push ebp 
mov ebp , esp 
mov eax , dword 3
mov ebx , dword [ebp  + 12]
cmp eax , ebx 
mov dword [ebp  + 8], eax 
