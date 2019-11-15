mov eax, 2
mov ebx, [ebp - 8]
mov ebx, [ebx + 4]
mov ebx, eax

banana_v: 
push ebp
mov ebp, esp

mov esp, ebp
pop ebp
ret

main: 
push ebp
mov ebp, esp

mov ecx, [ebp - 4]
push ecx
push [ebp - 4]
call banana_v

mov esp, ebp
pop ebp
ret

call main

