main: 
push ebp
mov ebp, esp

mov dword [ebp - 4], 1
mov dword [ebp - 8], 2
mov dword [ebp - 12], 3
mov dword [ebp - 16], 4
mov eax, [ebp - 8]
add eax, [ebp - 12]
sub eax, [ebp - 16]
imul eax, [ebp - 4]
mov [ebp - 4], eax

mov ebx, [ebp - 12]
xchg ebx, eax
cdq 
div dword [ebp - 16]
add ebx, eax
sub ebx, [ebp - 8]
mov [ebp - 8], ebx

mov ecx, [ebp - 16]
imul ecx, eax
xchg ecx, eax
cdq 
div ebx
add ecx, [ebp - 12]
mov [ebp - 12], ecx

sub eax, ebx
imul eax, ecx
xchg eax, eax
cdq 
div ecx
mov [ebp - 16], eax

mov esp, ebp
pop ebp
ret

