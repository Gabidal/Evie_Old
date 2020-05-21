_memcpy: 
push ebp 
mov ebp , esp 
xor ebx , ebx 
  _while4: 
  mov ecx, dword [ebp + 16]
  mov edx, ebx 
  cmp edx , ecx 
  jnl _while4END
  mov ecx, dword [ebp + 12]
  mov esi, dword [ecx  + ebx  * 4]
  mov ecx, dword [ebp + 8]
  lea edi, dword [ecx  + ebx  * 4]
  mov [edi ], esi 
  mov edx , ebx 
  add edx , dword 1
  mov ebx , edx 
  jmp _while4
_while4END: 
leave 
ret
 
_memcpyEND: 
export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 32
  mov [ebp - 28], dword 0
  mov [ebp - 32], dword 1
  push dword 1
  lea ecx, dword [ebp - 32]
  push ecx 
  lea edx, dword [ebp - 28]
  push edx 
  call _memcpy
  add esp , dword 12
  leave 
  ret
 
_mainEND: 
_MAX_BUFFER_SIZE: 
dd 123
