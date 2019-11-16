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
add ebx, [ebp - 12]
sub ebx, [ebp - 16]
imul ebx, [ebp - 4]
mov [ebp - 4], ebx

div ecx, [ebp - 16]
add ecx, [ebp - 4]
sub ecx, [ebp - 8]
mov [ebp - 8], ecx

imul edx, [ebp - 4]
div edx, [ebp - 8]
add edx, [ebp - 12]
mov [ebp - 12], edx

sub ebx, [ebp - 8]
imul ebx, [ebp - 12]
div ebx, [ebp - 16]
mov [ebp - 16], ebx

mov esp, ebp
pop ebp
ret

