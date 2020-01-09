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
 ; Adding b into a
 ; Just directly get address
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp - 4]
add eax, [ebp - 8]
 ; Adding a into a
 ; Just directly get address
 ; a has already a register to it
add eax, [ebp - 4]
 ; Adding b into a
 ; Just directly get address
 ; a has already a register to it
add eax, [ebp - 8]
mov [ebp - 12], eax
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
