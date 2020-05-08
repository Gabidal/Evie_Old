_memcpy: 
push ebp 
mov ebp , esp 
sub esp, dword 4
mov [ebp - 4], dword 0
_while37: 
mov ecx, dword [ebp + 16]
mov edx, dword [ebp - 4]
cmp edx , ecx 
jnl _while37END
mov ecx, dword [ebp - 4]
mov ecx, dword [ebp + 12]
mov esi, dword [ecx  + ecx * 4]
mov ecx , dword [ebp - 4]
mov ecx, dword [ebp + 8]
lea edi, dword [ecx  + ecx * 4]
mov [edi ], esi 
mov edx , dword [ebp - 4]
add edx , dword 1
mov [ebp - 4], edx 
jmp _while37
_while37END: 
xor al, al
leave 
ret
 
