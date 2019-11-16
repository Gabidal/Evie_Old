main: 
push ebp
mov ebp, esp

mov dword [ebp - 4], 2
mov dword [ebp - 8], 3
mov esp, ebp
pop ebp
ret

