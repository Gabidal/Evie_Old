%include "win32.asm"
export main
global main
main: 
  _main: 
  push dword 3
  push dword 2
  push dword 1
  call _print
  add esp, dword 12
  xor eax, eax
  ret
 
_mainEND: 
