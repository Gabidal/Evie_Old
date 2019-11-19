dsum: 
push ebp
mov ebp, esp

sub esp, 4

mov eax, [ebp + 8]
add eax, [ebp + 8]
mov [ebp + 8], eax

add eax, [ebp + 8]
mov [ebp + 8], eax

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

