global main
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 2
mov [ebp - 8], dword 2
 ; Multiplying b into a
 ; Just directly get address
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp - 4]
imul eax, [ebp - 8]
 ; Saving a into c
 ; a has already a register to it
mov [ebp - 12], dword eax
 ; Return c
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
