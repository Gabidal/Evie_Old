export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 16
  mov ecx, [ebp - 16]
  lea esi, dword [ecx  - 1 * 4]
  mov eax, esi 
  leave 
  ret
 
_mainEND: 
