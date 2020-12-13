extern _Z8allocatei
int:
ret 


short:
ret 


char:
ret 


float:
ret 


double:
ret 


long:
ret 


string:
ret 


Cat:
mov ecx, dword [rcx + 0 ]
mov qword [ecx ], dword 12
mov edx, dword [rcx + 4 ]
mov qword [edx ], dword 23
mov ecx, dword [rcx + 8 ]
mov qword [ecx ], dword 34
ret 


main:
mov ecx, dword 4
call _Z8allocatei
mov rcx, rax
call Cat
mov rcx, rax
mov eax, dword 0
ret 
ret 


