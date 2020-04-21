_banana: 
xor al , al 
ret
 
_apple: 
xor al , al 
ret
 
_orange: 
xor al , al 
ret
 
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 12
lea eax , dword [_banana]
lea ebx , dword [_apple]
lea ecx , dword [_orange]
_while29: 
mov dl , byte 2
mov  dh , byte 1
cmp  dh , dl 
jnl _while29END
call eax 
call ebx 
call ecx 
jmp _while29
_while29END: 
xor al , al 
leave 
ret
 
