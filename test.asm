_apple: 
mov al , byte 2
ret
 
_banana: 
mov al , byte 1
ret
 
export main
global main
main: 
_main: 
push dword 4
call _banana
add esp , dword 4
mov ebx , eax 
push dword 1
call _banana
add esp , dword 4
add eax , ebx 
ret
 
