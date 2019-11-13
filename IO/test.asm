banana(): 
push ebp
mov ebp, esp
mov eax, 3
mov ebx, [ebp - 4]
mov ebx, eax
mov ecx, 2998
mov edx, [ebp - 8]
mov edx, ecx
mov esi, [ebp - 12]
mov esi, ebx
imul esi, edx
imul esi, edx
mov esp, ebp
pop ebp
