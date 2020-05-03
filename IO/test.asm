export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
mov ecx, dword [ebp + 8]
add ecx , dword 1
mov edx, dword [ebp + 8]
add ecx , edx 
mov eax, ecx 
leave 
ret
 
