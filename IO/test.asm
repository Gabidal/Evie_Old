_main: 
push ebp 
mov ebp , esp 
sub esp , dword 8
mov ecx , [ebp - 4]
lea ebx , dword [ebp - -48]
mov [ebp - 8], ebx 
mov edx , dword [ebp - 8]
lea edi , dword [edx  - 1 * 4]
mov [edi ], dword 2
mov eax , dword 0
leave 
ret
 
_mainEND: 
