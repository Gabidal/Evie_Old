__Z6bananaP3int: 
push ebp 
mov ebp , esp 
mov eax, dword 0
leave 
ret
 
__Z6bananaP3intEND: 
export main
global main
main: 
  _main: 
  push dword 1
  call __Z6bananaP3int
  add esp, dword 4
  mov eax, dword 0
  ret
 
_mainEND: 
