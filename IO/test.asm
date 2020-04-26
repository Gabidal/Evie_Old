_main: 
push ebp 
mov ebp , esp 
mov ebx , dword [ebp  + 8]
lea ecx , dword [ebx  + 0 * 4]
mov eax , ecx 
leave 
ret
 
