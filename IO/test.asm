_good: 
push ebp 
mov ebp , esp 
lea ebx , dword [ebp  + 8]
mov eax , ebx 
leave 
ret
 
_same: 
push ebp 
mov ebp , esp 
lea ebx , dword [ebp  + 8]
mov eax , ebx 
leave 
ret
 
_bad: 
push ebp 
mov ebp , esp 
sub esp , dword 4
lea ebx , dword [ebp  + 8]
mov dword [ebp  - 4], ebx 
mov eax , dword [ebp  - 4]
leave 
ret
 
