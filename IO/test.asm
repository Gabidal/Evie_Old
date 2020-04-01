_banana: 
push ebp 
mov ebp , esp 
mov eax , dword [ebp  + 8]
mov ebx , dword [ebp  + 8]
imul eax , ebx 
leave 
ret
 
