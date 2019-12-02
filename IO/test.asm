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
 ; Private variable 
mov [ebp - 4], dword 1
 ; Giving b, 2
 ; Private variable 
mov [ebp - 8], dword 2
 ; Giving c, 3
 ; Private variable 
mov [ebp - 12], dword 3
 ; Adding c into b
 ; Just directly get address
 ; Private variable 
 ; Giving b eax
 ; Initializing new register for private  variable b
 ; Private variable 
mov eax, [ebp - 8]
add eax, [ebp - 12]
 ; Private variable 
mov [ebp - 4], eax

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Calling main
call main

