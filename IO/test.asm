_Z6banana5float: 
push ebp 
mov ebp , esp 
mov eax, dword 0
leave 
ret
 
_Z6banana5floatEND: 
_Z6banana3int: 
push ebp 
mov ebp , esp 
mov eax, dword 0
leave 
ret
 
_Z6banana3intEND: 
export main
global main
main: 
  _main: 
  mov ebx , dword 1.000000
  push dword 1.000000
  call _Z6banana5float
  add esp, dword 4
  mov ecx, eax
  push ebx 
  call _Z6banana5float
  add esp , dword 4
  add eax, ecx 
  mov eax, eax
  ret
 
_mainEND: 
