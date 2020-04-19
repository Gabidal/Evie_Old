_banana: 
xor al , al 
ret
 
export main
global main
main: 
_main: 
lea eax , dword [_banana]
mov dword [ebp  - 4], eax 
_while29: 
mov al , byte 1
mov ah , byte 2
cmp al , ah 
jnl _while29END
push dword 1
call [ebp  - 4]
add esp , dword 4
jmp _while29
_while29END: 
xor al , al 
ret
 
