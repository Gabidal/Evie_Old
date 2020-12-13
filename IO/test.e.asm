extern _Z8allocatei
_Z3CatP3Cat:
mov dword [rcx + 0 ], dword 12
mov dword [rcx + 4 ], dword 23
mov dword [rcx + 8 ], dword 34
ret 


_Z4mainv:
mov ecx, dword 4
call _Z8allocatei
mov rcx, rax
call _Z3CatP3Cat
mov rcx, rax
mov eax, dword 0
ret 
ret 


