export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 32
  lea ecx, dword [ebp - 4]
  mov [ebp - 28], ecx 
  mov edx, dword [ebp - 28]
  lea edi, dword [edx  + 0 * 4]
  mov [edi ], dword 12
  mov edx , dword [ebp - 28]
  lea edi , dword [edx  + 4 * 4]
  mov [edi ], dword 3
  mov edx , dword [ebp - 28]
  lea edi , dword [edx  + 8 * 4]
  mov [edi ], dword 5
  mov [ebp - 32], dword 1
  leave 
  ret
 
_mainEND: 
