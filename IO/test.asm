main: 
push ebp
mov ebp, esp

mov eax, 1
mov [ebp - 4], eax

mov ebx, 2
mov [ebp - 8], ebx

mov ecx, 3
mov [ebp - 12], ecx

mov edx, 4
mov [ebp - 16], edx

mov esi, [ebp - 8]
add esi, [ebp - 12]

sub esi, [ebp - 16]

imul esi, [ebp - 4]

mov [ebp - 4], esi

mov edi, [ebp - 12]
div edi, [ebp - 16]

add edi, [ebp - 4]

sub edi, [ebp - 8]

mov [ebp - 8], edi

mov null, [ebp - 16]
imul null, [ebp - 4]

div null, [ebp - 8]

add null, [ebp - 12]

mov [ebp - 12], null

sub esi, [ebp - 8]

imul esi, [ebp - 12]

div esi, [ebp - 16]

mov [ebp - 16], esi

mov esp, ebp
pop ebp
ret

