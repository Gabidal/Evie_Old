_banana: 
push eax 
call _banana
mov ebx , dword [ebp  + 12]
add ebx , eax 
push ebx 
call _banana
mov ecx , dword [ebp  + 8]
add ecx , eax 
push ecx 
call _banana
leave 
ret
 
