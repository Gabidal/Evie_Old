section .bss
section .code
 ; Function sum
sum: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 0

 ; Adding y into x
 ; Just directly get address
 ; Giving x, eax
 ; Initializing new register for private  variable x
mov eax, [ebp + 4]
add eax, [ebp + 8]
 ; Saving result of x into x
mov [ebp + 4], eax

 ; x has already a register to it
 ; Return x
 ; Giving Returning address, ebx
mov esp, ebp
pop ebp
pop ebx
push eax
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

 ; Giving b, 2
mov [ebp - 4], dword 2
 ; Giving c, 3
mov [ebp - 12], dword 3
 ; Calling sum
 ; Pushing Variable 
 ; Giving b, ecx
 ; Initializing new register for private  variable b
mov ecx, [ebp - 4]
push ecx
 ; Pushing Variable 
 ; Giving c, edx
 ; Initializing new register for private  variable c
mov edx, [ebp - 12]
push edx
call sum

 ; Clearing the parameters
add esp, 8
 ; Giving a the return value
pop dword [ebp - 20]

 ; Giving a, esi
 ; Initializing new register for private  variable a
mov esi, [ebp - 20]
 ; Return a
 ; Giving Returning address, edi
mov esp, ebp
pop ebp
pop edi
push esi
jmp edi

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

