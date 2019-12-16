raw_print: 
pop edx
pop ecx
mov ebx, 1
mov eax, 4
int 80h
ret 
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 4

 ; Givinga the address ofS0
 ; Giving a, eax
lea eax, [S0]
 ; Calling raw_print
push 12
 ; Pushing pointter 
push eax
call raw_print

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

section .bss
section .data
S0
 db "Hello World!"
