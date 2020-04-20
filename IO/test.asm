_banana: 
xor al , al 
ret
 
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 8
lea eax , dword [_banana]
mov dword [ebp  - 4], eax 
mov ebx , dword [ebp  - 4]
mov dword [ebp  - 8], ebx 
_while29: 
mov cl , byte 1
mov ch , byte 2
cmp cl , ch 
jnl _while29END
push dword 1
call [ebp  - 4]
add esp , dword 4
jmp _while29
_while29END: 
xor al , al 
leave 
ret
 
