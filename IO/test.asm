export main
global main
main: 
_main: 
mov eax , dword [(_ptr) + 0 * 4]
lea ebx , dword [(_ptr) + 0 * 4]
mov eax , ebx 
ret
 
_ptr: 
db "banana"
