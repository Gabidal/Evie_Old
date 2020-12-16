extern _Z8allocatei
_Z3CatP3Cat:
mov dword [rcx + 0 ], dword 12
mov dword [rcx + 4 ], dword 23
mov dword [rcx + 8 ], dword 34
ret 


Get_Speed:
mov eax, dword 1
ret 
ret 


_Z4mainv:
push rbx
push rbx
mov ecx, dword 4
call _Z8allocatei
mov rcx, rax
call _Z3CatP3Cat
mov rcx, rax
mov rbx, rcx
call Get_Speed
mov ecx, ebx
mov eax, dword 0
pop rbx
pop rbx
ret 
pop rbx
pop rbx
ret 


