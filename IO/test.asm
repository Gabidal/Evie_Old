banana: 
push ebp
mov ebp, esp

sub esp, 0

mov esp, ebp
pop ebp
ret

main: 
push ebp
mov ebp, esp

sub esp, 8

mov dword [ebp - 4], 2
mov dword [ebp - 8], 3
mov eax, [ebp - 8]
push eax
call banana

mov esp, ebp
pop ebp
ret

