main: 
push ebp
mov ebp, esp

mov eax, 1
mov [ebp - 4], eax

mov ebx, [ebp - 4]
add ebx, 2

add ebx, 1

add ebx, ebx

mov [ebp - 4], ebx

mov ecx, 1
mov [ebp - 8], ecx

mov edx, [ebp - 8]
add edx, 2

add edx, 1

add edx, edx

mov [ebp - 8], edx

mov esp, ebp
pop ebp
ret

