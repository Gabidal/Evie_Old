_banana: 
xor eax , eax 
ret
 
_bananaEND: 
export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp , dword 16
  call _banana
  xor ecx , ecx 
  add ecx , dword 1
  mov [ebp - 4], ecx 
  mov edx , dword 1
  add edx , dword 2
  mov [ebp - 8], edx 
  mov ecx , dword 2
  add ecx , dword 3
  mov [ebp - 12], ecx 
  mov ecx , dword 3
  add ecx , dword 4
  mov [ebp - 16], ecx 
  mov eax , dword [ebp - 16]
  leave 
  ret
 
_mainEND: 
