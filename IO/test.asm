extern sys_print
_sys_print: 
_sys_printEND: 
export main
global main
main: 
  _main: 
  push dword 14
  lea ecx, dword [_banana]
  push ecx 
  call sys_print
  add esp, dword 8
  xor eax, eax
  ret
 
_mainEND: 
_banana: 
db "kurkkujugurtti"
