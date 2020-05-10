_memcpy: 
push ebp 
mov ebp , esp 
xor ebx , ebx 
_while37: 
mov ecx, dword [ebp + 16]
mov edx, ebx 
cmp edx , ecx 
jnl _while37END
mov ecx, dword [ebp + 12]
mov esi, dword [ecx  + ebx  * 4]
mov ecx, dword [ebp + 8]
lea edi, dword [ecx  + ebx  * 4]
mov [edi ], esi 
mov edx , ebx 
add edx , dword 1
mov ebx , edx 
jmp _while37
_while37END: 
_if38: 
mov ecx, ebx 
cmp ecx , dword 0
jnl _if38END
mov al, byte 1
leave 
ret
 
_if38END: 
xor al, al
leave 
ret
 
_memcpyEND: 
