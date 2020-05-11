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
  call _memcpy
_mainEND: 
