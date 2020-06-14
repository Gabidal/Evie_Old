_Z6banana5float: 
push ebp 
mov ebp , esp 
mov eax, dword 0
leave 
ret
 
_Z6banana5floatEND: 
_Z6bananaP3int: 
push ebp 
mov ebp , esp 
mov eax, dword 0
leave 
ret
 
_Z6bananaP3intEND: 
export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 4
  mov [ebp - 4], dword 1.000000
  push dword 1
  call _Z6bananaP3int
  add esp , dword 4
  push dword [ebp - 4]
  call _Z6banana5float
  add esp , dword 4
  mov eax, dword 0
  leave 
  ret
 
_mainEND: 
