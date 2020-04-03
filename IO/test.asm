_banana: 
push ebp 
mov ebp , esp 
push dword [ebp  + 12]
call _banana
add esp , dword 4
push eax 
push dword [ebp  + 8]
call _banana
add esp , dword 8
leave 
ret
 
