section .bss
section .code
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 0

 ; Allocating new memory space for new type 
push dword 12
call malloc
pop dword [ebp - 4]
 ; Giving v, eax
 ; Initializing new register for private  variable v
mov eax, [ebp - 16]
 ; Return v
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

