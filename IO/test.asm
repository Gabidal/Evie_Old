_banana: 
push eax 
call _banana
mov ebx , dword [ebp  + 8]
mov ecx , dword [ebp  + 12]
add ebx , ecx 
add ebx , eax 
push ebx 
call _banana
mov edx , dword [ebp  + 12]
add edx , eax 
push edx 
call _banana
mov ebx , dword [ebp  + 8]
add ebx , eax 
push ebx 
call _banana
leave 
ret
 
