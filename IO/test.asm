export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 24
  mov dword [(ebp - 4) + 8], dword 0
  leave 
  ret
 
_mainEND: 
