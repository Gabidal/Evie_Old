_banana: 
xor al , al 
ret
 
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 4
lea eax , dword [_banana]
mov dword [ebp  - 4], eax 
_while29: 
mov bl , byte 1
mov bh , byte 2
cmp bl , bh 
jnl _while29END
push dword 1
call [ebp  - 4]
add esp , dword 4
jmp _while29
_while29END: 
xor al , al 
leave 
ret
 
