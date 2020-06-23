_banana: 
push ebp 
mov ebp , esp 
sub esp , dword 4
mov ecx , dword [ebp + 28]
mov ebx , dword [ebp + 24]
imul ebx , ecx 
mov edx , dword [ebp + 20]
mov edi , dword [ebp + 16]
imul edi , edx 
mov ecx , dword [ebp + 12]
mov esi , dword [ebp + 8]
imul esi , ecx 
add esi , edi 
sub esi , ebx 
mov [ebp - 4], esi 
mov eax , dword [ebp - 4]
leave 
ret
 
_bananaEND: 
export main
global main
main: 
  _main: 
  push dword 6
  push dword 5
  push dword 4
  push dword 3
  push dword 2
  push dword 1
  call _banana
  add esp , dword 24
  ret
 
_mainEND: 
