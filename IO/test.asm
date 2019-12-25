extern _VirtualAlloc@16
global malloc
malloc: 
push dword 0x04
push dword 0x3000
push dword [esp + 8]
push dword 0
call _VirtualAlloc@16
ret 

 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 8

 ; Allocating new memory space for new type 
push 8
call malloc
 ; Saving b into b
 ; b has already a register to it
mov [ebp - 4], dword eax
 ; Return b
 ; Giving Returning address, eax
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
