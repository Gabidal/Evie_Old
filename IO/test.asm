_banana: 
xor al , al 
ret
 
_apple: 
xor al , al 
ret
 
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 8
lea ebx , dword [_banana]
lea ecx , dword [_apple]
_while29: 
mov dl , byte 2
mov  dh , byte 1
cmp  dh , dl 
jnl _while29END
call ebx 
call ecx 
jmp _while29
_while29END: 
xor al , al 
leave 
ret
 
