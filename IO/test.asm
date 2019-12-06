section .bss
true resd 1
section .code
 ; Function init
init: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 0

 ; Giving true, 1
mov [true], dword 1
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
sub esp, 0

 ; Return true
 ; Giving Returning address, eax
mov esp, ebp
pop ebp
pop eax
push dword [true]
jmp eax

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

