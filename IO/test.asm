extern _createApple
__createApple: 
__createAppleEND: 
export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 4
  mov ecx, dword [_MAX_BUFFER_SIZE]
  add ecx , dword 1
  mov [ebp - 4], ecx 
  call _createApple
  mov edx, dword [ebp - 4]
  add eax, edx 
  leave 
  ret
 
_mainEND: 
_MAX_BUFFER_SIZE: 
dd 123
