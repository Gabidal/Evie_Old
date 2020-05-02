_memcpy: 
push ebp 
mov ebp , esp 
mov [], dword 0
_while37: 
mov , 
mov , 
cmp , 
jnl _while37END
mov , 
mov , 
mov , dword [ +  * 4]
mov , 
mov dword [ +  * 4], 
mov , 
add , dword 1
mov [], 
jmp _while37
_while37END: 
xor al, al
leave 
ret
 
