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
mov [ebp - 8], dword 3
 ; Calling sum
 ; Pushing Variable 
push [ebp - 4]
 ; Pushing Variable 
push [ebp - 8]
call sum

 ; Clearing the parameters
add esp, 8
 ; Giving a the return value
pop dword [ebp - 12]

 ; Giving a, ecx
 ; Initializing new register for private  variable a
mov ecx, [ebp - 12]
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

