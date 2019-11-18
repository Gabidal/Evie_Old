banana: 
push ebp
mov ebp, esp

sub esp, 4

mov eax, [ebp + 4]
add eax, [ebp + 4]
mov [ebp + 4], eax

mov esp, ebp
pop ebp
ret

main: 
push ebp
mov ebp, esp

sub esp, 8

mov dword [ebp - 4], 2
mov dword [ebp - 8], 3
mov ebx, [ebp - 4]
add ebx, [ebp - 4]
call banana

pop ebx

imul ebx, [ebp - 8]
mov [ebp - 8], ebx

mov esp, ebp
pop ebp
ret

