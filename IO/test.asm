global main
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 4

 ; Calling yeet
call yeet

 ; Adding b into a
 ; Just directly get address
 ; Giving a, eax
 ; Initializing new register for public variable a
mov eax, [a]
add eax, [b]
 ; Saving a into d
 ; a has already a register to it
mov [ebp - 4], dword eax
if0: 
 ; Comparing d and 2
 ; Just directly get name of the number
 ; Giving 2, ebx
mov ebx, 2
cmp [ebp - 4], ebx
 ; Jumping source: '=='
jne else1
 ; Return 1
 ; Giving Returning address, ecx
mov eax, 1
mov esp, ebp
pop ebp
ret 

if0END: 
jmp else1END

else1: 
 ; Return 2
 ; Giving Returning address, edx
mov eax, 2
mov esp, ebp
pop ebp
ret 

else1END: 
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Calling main
call main

section .bss
b resd 1
section .data
