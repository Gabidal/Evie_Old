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
_while29: 
mov bl , byte 2
mov bh , byte 1
cmp bh , bl 
jnl _while29END
push dword 1
call eax 
add esp , dword 4
jmp _while29
_while29END: 
xor al , al 
leave 
ret
 
