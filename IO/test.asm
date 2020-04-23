_banana: 
xor al , al 
ret
 
_apple: 
xor ah , ah 
ret
 
_orange: 
xor al , al 
ret
 
_pear: 
xor ah , ah 
ret
 
_melon: 
xor al , al 
ret
 
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 16
lea ebx , dword [_banana]
lea ecx , dword [_apple]
lea edx , dword [_orange]
mov dword [ebp  - 12], edx 
lea edi , dword [_pear]
mov dword [ebp  - 16], edi 
_while29: 
mov bl , byte 2
mov bh , byte 1
cmp bh , bl 
jnl _while29END
call ebx 
call ecx 
call [ebp  - 12]
call [ebp  - 16]
jmp _while29
_while29END: 
xor al , al 
leave 
ret
 
