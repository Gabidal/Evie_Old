 ; Function s
s: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Adding b into a
 ; Just directly get address
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp + 4]
add eax, [ebp + 8]
 ; Saving a into a
 ; a has already a register to it
mov [ebp + 4], dword eax
 ; Return a
 ; Giving Returning address, ebx
mov esp, ebp
pop ebp
ret 

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
sub esp, 4

 ; Calling s
push 1
push 2
call s

 ; Clearing the parameters
add esp, 8
 ; Direct addition
 ; s has already a register to it
add eax, dword 32
 ; Direct addition
 ; 32 has already a register to it
add eax, dword 12
 ; Saving a into a
 ; a has already a register to it
mov [ebp - 4], dword eax
 ; Return a
 ; Giving Returning address, ecx
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Calling main
call main

section .bss
