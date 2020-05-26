export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 24
  mov ecx, dword [ebp - 12]
  mov esi, dword [ecx  + 0 * 12]
  mov [ebp - 24], esi 
  leave 
  ret
 
_mainEND: 
