export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 4
  mov ecx, [ebp + 20]
  lea esi, dword [ecx  + 10 * 4]
  mov [ebp - 4], esi 
  mov eax, dword [ebp - 4]
  leave 
  ret
 
_mainEND: 
