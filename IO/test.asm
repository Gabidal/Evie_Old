push dword 3
push dword 2
push dword 1
call _onUpdate
add esp , dword 12
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 8
lea ebx , dword [_onUpdate]
mov dword [ebp  - 4], ebx 
mov eax , dword [ebp  - 4]
leave 
ret
 
_onUpdate: 
dd 1
_a: 
dd (_onUpdate)
