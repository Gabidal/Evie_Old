export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 21
  lea ecx, dword [(ebp - 16) - 10 * 4]
  mov [ebp - 20], ecx 
  mov [ebp - 24], byte 0
  push dword 1
  push byte [ebp - 24]
  call _banana
  add esp , dword 5
  mov eax, dword [ebp - 20]
  leave 
  ret
 
_mainEND: 
  _banana: 
  push ebp 
  mov ebp , esp 
  xor eax, eax
  leave 
  ret
 
_bananaEND: 
_MAX_BUFFER_SIZE: 
dd 123
