export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 24
  mov ecx, dword [(ebp - 4) + 0]
  mov edx, dword 0
  add edx , ecx 
  add edx , dword 1
  mov dword [(ebp - 4) + 8], edx 
  leave 
  ret
 
_mainEND: 
