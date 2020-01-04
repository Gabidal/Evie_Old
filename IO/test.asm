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
 ; Multiplying b into c
 ; Just directly get address
 ; Giving c, eax
 ; Initializing new register for private  variable c
mov eax, [ebp - 12]
imul eax, [ebp - 8]
 ; Adding a into c
 ; Just directly get address
 ; c has already a register to it
add eax, [ebp - 4]
mov [ebp - 16], eax
 ; Adding c into d
 ; Just directly get address
 ; Giving d, eax
 ; Initializing new register for private  variable d
mov eax, [ebp - 16]
add eax, [ebp - 12]
 ; Dividing b into d
 ; Just directly get address
idiv dword [ebp - 8]
 ; Multiplying a into d
 ; Just directly get address
 ; d has already a register to it
imul eax, [ebp - 4]
mov [ebp - 20], eax
 ; Return e
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
