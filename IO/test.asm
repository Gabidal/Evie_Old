export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 25
  lea ecx, dword [(ebp - 4) + 8]
  mov [ebp - 28], ecx 
  mov edx, dword [ebp - 28]
  lea edi, dword [edx  + 1 * 1]
  mov [edi ], dword 1
  leave 
  ret
 
_mainEND: 
