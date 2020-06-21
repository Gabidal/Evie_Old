extern sys_print
_sys_print: 
_sys_printEND: 
export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 4
  mov ecx, "kurkkujugurtti"
  mov [ebp - 4], ecx 
  push dword 14
  lea edx, dword [ebp - 4]
  push edx 
  call sys_print
  add esp , dword 8
  xor eax, eax
  leave 
  ret
 
_mainEND: 
