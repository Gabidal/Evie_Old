_memcpy: 
push ebp 
mov ebp , esp 
xor ebx , ebx 
_while37: 
mov ebx , dword [ebp  + 16]
mov ecx , ebx 
cmp ecx , ebx 
jnl _while37END
mov edx , ebx 
mov edi , dword [ebp  + 12]
mov esi , dword [edi  + edx  * 4]
mov ebx , dword [ebp  + 8]
mov dword [ebx  + ebp  - 0 * 4], esi 
mov ecx , ebx 
add ecx , dword 1
mov [ebx ], ecx 
jmp _while37
_while37END: 
xor al , al 
leave 
ret
 
