_banana: 
push ebp 
mov ebp , esp 
sub esp , dword 8
xor ebx , ebx 
mov dword [ebp  - 4], ebx 
mov ecx , dword 3
mov edx , dword [ebp  - 16]
imul ecx , edx 
mov edi , dword [ebp  - 12]
add ecx , edi 
mov dword [ebp  - 4], ecx 
push dword [ebp  + 8]
push dword [ebp  - 12]
call _banana
add esp , dword 8
mov esi , dword [ebp  - 12]
mov edi , dword [ebp  - 12]
imul esi , edi 
add esi , eax 
mov dword [ebp  - 16], esi 
mov eax , dword [ebp  + 8]
mov eax , dword [ebp  + 8]
add eax , eax 
mov dword [ebp  - 12], eax 
_push[ebp  - 0]
_push[ebp  - 0]
_push[ebp  - 0]
call _b
add esp , dword 8
mov eax , dword [ebp  + 8]
cmp eax , eax 
jng _bananaEND
mov eax , dword [ebp  + 8]
mov ebx , dword [ebp  + 12]
add eax , ebx 
mov ecx , dword [ebp  - 4]
sub eax , ecx 
_convertal , eax 
leave 
ret
 
