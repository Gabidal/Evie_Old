dsum: 
push ebp
mov ebp, esp

sub esp, 8

mov eax, [ebp + 8]
mov ebx, [ebp + 4]
add ebx, [eax + 4]
mov [ebx + 4], ebx

mov ecx, [ebp + 8]
mov edx, [ebp + 4]
add edx, [ecx + 0]
mov [edx + 0], edx

mov esp, ebp
pop ebp
ret

main: 
push ebp
mov ebp, esp

sub esp, 8

call dsum

mov esp, ebp
pop ebp
ret

