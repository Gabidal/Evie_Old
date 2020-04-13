push dword 3
push dword 2
push dword 1
call _onUpdate
add esp , dword 12
_onUpdate: 
mov al , byte 1
ret
 
