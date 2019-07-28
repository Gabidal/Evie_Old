a dd 1
b dd 2
c dd 3

mov eax , dword [b]
mov [a], eax 
mov ebx , dword [b]
mov ecx , dword [c]
add ebx , ecx 
mov [a], ebx 
