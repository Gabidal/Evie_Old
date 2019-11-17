main: 
push ebp
mov ebp, esp

sub esp, 12

mov dword [ebp - 4], 2
mov dword [ebp - 8], 3
while0: 
mov dword [ebp - 12], 1
mov eax, [ebp - 4]
add eax, 1
mov [ebp - 4], eax

cmp eax, [ebp - 8]
jg while0END
while0END: 
mov esp, ebp
pop ebp
ret

