section .bss
section .code
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 4

 ; Giving opt, eax
 ; Initializing new register for private  variable opt
mov eax, [ebp - 4]
 ; Return opt
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

