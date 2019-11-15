mov eax, 2
mov ebx, [ebp - 8]
mov ebx, [ebx + 4]
mov ebx, eax

banana_v: 
push ebp
mov ebp, esp

mov esp, ebp
pop ebp
ret

main: 
push ebp
mov ebp, esp

mov ecx, 3
mov edx, [ebp - 4]
mov edx, ecx

add ebx, edx

add ebx, edx

mov esp, ebp
pop ebp
ret

