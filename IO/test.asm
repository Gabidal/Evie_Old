section .bss
section .code
 ; Function sum
sum: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 0

 ; Adding b into a
 ; Just directly get address
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp + 4]
add eax, [ebp + 8]
 ; Saving result of a into a
mov [ebp + 4], eax

 ; a has already a register to it
 ; Return a
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

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 2
mov [ebp - 8], dword 2
 ; Giving c, 3
mov [ebp - 12], dword 3
 ; Calling sum
 ; Pushing Variable 
 ; Giving b, ecx
 ; Initializing new register for private  variable b
mov ecx, [ebp - 8]
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
pop dword [ebp - 4]

 ; Giving a, esi
 ; Initializing new register for private  variable a
mov esi, [ebp - 4]
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

 ; Calling main
call main

