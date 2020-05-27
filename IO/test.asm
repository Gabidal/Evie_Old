export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 20
  lea ecx, dword [(ebp - 16) - 10 * 4]
  mov [ebp - 20], ecx 
  mov eax, dword [ebp - 20]
  leave 
  ret
 
_mainEND: 
