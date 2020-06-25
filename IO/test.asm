export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp , dword 4
  xor cl , cl 
  add cl , byte 1
  mov [ebp - 4], cl 
  mov ch , byte 1
  add ch , byte 2
  mov [ebp - 5], ch 
  mov dl , byte 2
  add dl , byte 3
  mov [ebp - 6], dl 
  mov cl , byte 3
  add cl , byte 4
  mov [ebp - 7], cl 
  mov eax , byte [ebp - 7]
  leave 
  ret
 
_mainEND: 
