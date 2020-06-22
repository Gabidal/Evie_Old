_f: 
push ebp 
mov ebp , esp 
sub esp, dword 4
mov ecx, dword [ebp + 20]
mov edx, dword [ebp + 16]
imul edx , ecx 
sub , dword 4
add esp , dword 4
mov edx , dword [ebp + 12]
mov ecx, dword [ebp + 8]
imul ecx , edx 
sub , dword 4
add esp , dword 4
add ecx , edx 
mov [ebp - 4], ecx 
mov eax, dword [ebp - 4]
leave 
ret
 
_fEND: 
export main
global main
main: 
  _main: 
  push dword 4
  push dword 3
  push dword 2
  push dword 1
  call _f
  add esp, dword 16
  ret
 
_mainEND: 
