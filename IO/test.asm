push dword 3
push dword 2
push dword 1
call _onUpdate
add esp , dword 12
_onUpdate: 
dd 1
_a: 
dd (_onUpdate)
