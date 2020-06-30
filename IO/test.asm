extern sys_print
_sys_print: 
_sys_printEND: 
export main
global main
main: 
  _main: 
  push dword 6
  push _S0
  call sys_print
  add esp , dword 8
  xor eax , eax 
  ret
 
_mainEND: 
_S0: 
db "hello!"
