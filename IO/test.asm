section .bss
section .code
 ; Function sum
sum: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Adding y into x
 ; Just directly get address
 ; Giving x, eax
 ; Initializing new register for private  variable x
mov eax, [ebp + 4]
add eax, [ebp + 8]
 ; Saving x into x
 ; x has already a register to it
mov [ebp + 4], dword eax
 ; Return x
 ; Giving Returning address, ebx
 ; Giving x, ecx
 ; Initializing new register for private  variable x
mov ecx, [ebp + 4]
mov esp, ebp
pop ebp
pop ebx
push ecx
jmp ebx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 12

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 2
mov [ebp - 8], dword 2
 ; Giving c, 3
mov [ebp - 12], dword 3
 ; Calling sum
 ; Pushing Variable 
push [ebp - 8]
 ; Pushing Variable 
push [ebp - 12]
call sum

 ; Clearing the parameters
add esp, 8
 ; Giving a the return value
pop dword [ebp - 4]

 ; Return a
 ; Giving Returning address, edx
 ; Giving a, esi
 ; Initializing new register for private  variable a
mov esi, [ebp - 4]
mov esp, ebp
pop ebp
pop edx
push esi
jmp edx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

