export banana
banana: 
_banana: 
push ebp 
mov ebp , esp 
sub esp , dword 4
mov eax , dword 0
mov dword [ebp  - 4], eax 
_if4: 
mov ebx , dword [ebp  + 8]
mov eax , dword 0
cmp ebx , eax 
jnl _if4END
movsx ecx , al 
mov ecx , ecx 
mov al , al 
mov dword [ebp  - 4], ecx 
mov eax , dword [ebp  - 4]
leave 
ret
 
_if4END: 

_if5: 
mov edx , dword [ebp  + 8]
jne _if5END
mov eax , dword [ebp  - 4]
leave 
ret
 
_if5END: 
mov eax , dword [ebp  - 4]

leave 
ret
 
