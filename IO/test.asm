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
mov al , byte 1
leave 
ret
 
global main
main: 
_if4: 
mov ebx , dword [ebp  + 8]
mov ah , byte 1
movsx ebx , ah 
cmp ebx , ebx 
jne _if4END
mov ah , byte 1
ret
 
_if4END: 
_if5: 
mov ecx , dword [ebp  + 8]
mov bl , byte 1
movsx ecx , bl 
cmp ecx , ecx 
je _if5END
mov al , byte 2
ret
 
_if5END: 
