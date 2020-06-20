extern print
_print: 
_printEND: 
export main
global main
main: 
  _main: 
  push dword 3
  push dword 2
  push dword 1
  call print
  add esp, dword 12
  ret
 
_mainEND: 
