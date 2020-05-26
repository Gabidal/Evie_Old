export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 16
  mov ecx, dword [ebp - 12]
  lea esi, dword [ecx  + 0 * 4]
  mov [ebp - 16], esi 
  mov eax, dword [ebp - 16]
  leave 
  ret
 
_mainEND: 
