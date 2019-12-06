section .bss
true resd 1
false resd 1
null resd 1
size_v resd 1
size_f resd 1
size_d resd 1
size_c resd 1
section .code
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 0

 ; Giving 1, eax
 ; Initializing new register for number 1
mov eax, 1
 ; Return 1
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

