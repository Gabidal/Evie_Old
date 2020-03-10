global _start
_start: 
push ebp 
mov ebp , esp 
mov al , byte 1
movsx eax , al 
mov eax , eax 
mov [ebp  - 4], eax 
push dword [ebp  - 4]
call main
mov eax , dword [ebp  - 4]
leave 
ret
 
global main
main: 
_if4: 
mov ebx , dword [ebp  + 8]
mov ah , byte 1
movsx ecx , ah 
cmp ebx , ecx 
jne _if4END
mov ah , byte 1
ret
 
_if4END: 
_if5: 
mov edx , dword [ebp  + 8]
mov bl , byte 1
movsx edi , bl 
cmp edx , edi 
je _if5END
mov eax , dword -1.0
ret
 
_if5END: 
