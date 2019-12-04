section .bss
section .code
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
mov [ebp - 12], dword 2
 ; Giving c, 3
mov [ebp - 20], dword 3
 ; Calling sum
 ; Pushing Variable 
 ; Giving b, eax
 ; Initializing new register for private  variable b
mov eax, [ebp - 12]
push eax
 ; Pushing Variable 
 ; Giving c, ebx
 ; Initializing new register for private  variable c
mov ebx, [ebp - 20]
push ebx
call sum

 ; Clearing the parameters
add esp, 8
 ; Giving a the return value
pop dword [ebp - 4]

 ; Adding size into a
 ; Just directly get address
 ; Giving a, ecx
 ; Initializing new register for private  variable a
mov ecx, [ebp - 4]
add ecx, [ebp - 4]
 ; Saving result of a into a
mov [ebp - 4], ecx

 ; a has already a register to it
 ; Return a
 ; Giving Returning address, edx
mov esp, ebp
pop ebp
pop edx
push ecx
jmp edx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

