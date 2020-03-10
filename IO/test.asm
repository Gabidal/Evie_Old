global _start
_start: 
push ebp 
mov ebp , esp 
mov eax , dword 1.0
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
mov ecx , dword 1.0
cmp ebx , ecx 
jne _if4END
mov al , byte 1
ret
 
_if4END: 
_if5: 
mov edx , dword [ebp  + 8]
mov edi , dword 1.0
cmp edx , edi 
je _if5END
mov eax , dword -1.0
ret
 
_if5END: 
