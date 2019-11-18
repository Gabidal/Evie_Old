banana: 
push ebp
mov ebp, esp

sub esp, 4

mov eax, [ebp + 8]
add eax, [ebp + 8]
mov [ebp + 8], eax

mov esp, ebp
pop ebp
pop ebx
push dword [ebp + 8]
jmp ebx

mov esp, ebp
pop ebp
ret

main: 
push ebp
mov ebp, esp

sub esp, 8

mov dword [ebp - 4], 2
mov dword [ebp - 8], 3
mov ecx, [ebp - 4]
push ecx
call banana

add esp, 4
pop ecx

imul ecx, [ebp - 8]
mov [ebp - 8], ecx

mov esp, ebp
pop ebp
ret

