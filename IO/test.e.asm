_Z4mainv:
push rbx
mov ecx, dword 1
mov edx, ecx
xor ebx, ebx
mov eax, dword 2
div edx
mov edx, eax
mov ecx, edx
mov eax, ecx
pop rbx
ret 
pop rbx
ret 


