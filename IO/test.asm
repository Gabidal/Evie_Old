_memcpy: 
push ebp 
mov ebp , esp 
sub esp , dword 4
mov [ebp  - 4], dword 0
_while37: 
mov ebx , dword [ebp  + 16]
mov ecx , dword [ebp  - 4]
cmp ecx , ebx 
jnl _while37END
mov edx , dword [ebp  - 4]
mov edi , dword [ebp  + 12]
mov esi , dword [edi  + edx  * 4]
mov ebx , dword [ebp  + 8]
mov dword [ebx  + ebp  - 4 * 4], esi 
mov ecx , dword [ebp  - 4]
add ecx , dword 1
mov [ebp  - 4], ecx 
jmp _while37
_while37END: 
xor al , al 
leave 
ret
 
