_a: 
push ebp 
mov ebp , esp 
call [ebp  + 8]
mov ebx , dword [ebp  + 8]
mov ecx , dword [ebx  + 0 * 4]
add ecx , eax 
mov ebx , dword 1
add ecx , ebx 
mov eax , ecx 
leave 
ret
 
_b: 
push ebp 
mov ebp , esp 
call [ebp  + 8]
mov ebx , dword [(ebp  + 8) + 0 * 4]
add ebx , eax 
mov ebx , dword 1
add ebx , ebx 
mov eax , ebx 
leave 
ret
 
_c: 
push ebp 
mov ebp , esp 
call [ebp  + 8]
lea ebx , dword [ebp  + 8]
add ebx , eax 
mov ebx , dword 1
add ebx , ebx 
mov eax , ebx 
leave 
ret
 
