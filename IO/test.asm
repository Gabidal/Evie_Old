_banana: 
push ebp 
mov ebp , esp 
mov eax , dword [ebp  + 8]
mov ebx , dword [ebp  + 8]
imul eax , ebx 
leave 
ret
 
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 8
mov dword [ebp  - 4], dword 1
mov dword [ebp  - 8], dword 2
push dword [ebp  - 8]
call _banana
add esp , dword 4
mov edi , dword [ebp  - 4]
add edi , eax 
mov eax , edi 
leave 
ret
 
