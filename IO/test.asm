export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 24
  mov ecx, dword [(ebp - 4) + 16]
  mov [ebp - 24], ecx 
  leave 
  ret
 
_mainEND: 
