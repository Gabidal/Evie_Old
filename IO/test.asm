extern sys_print
_sys_print: 
_sys_printEND: 
export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp , dword 4
  push dword 6
  push _S0
  call sys_print
  add esp , dword 8
  mov ecx , _S0
  mov [ebp - 4], ecx 
  xor eax , eax 
  leave 
  ret
 
_mainEND: 
_S0: 
db "hello!"
