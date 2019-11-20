a: 
push ebp
mov ebp, esp

sub esp, 4

mov esp, ebp
pop ebp
pop eax
push dword [ebp + 4]
jmp eax

mov esp, ebp
pop ebp
ret

c: 
push ebp
mov ebp, esp

sub esp, 4

mov esp, ebp
pop ebp
pop ebx
push dword [ebp + 4]
jmp ebx

mov esp, ebp
pop ebp
ret

