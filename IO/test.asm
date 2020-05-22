export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 32
  mov [ebp - 28], dword 0
  mov [ebp - 32], dword 1
  leave 
  ret
 
_mainEND: 
_MAX_BUFFER_SIZE: 
dd 123
