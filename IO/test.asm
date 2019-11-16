main: 
push ebp
mov ebp, esp

mov eax, [ebp - 4]
add eax, 2

mov ebx, 2
add eax, ebx

mov [ebp - 4], eax

mov esp, ebp
pop ebp
ret

