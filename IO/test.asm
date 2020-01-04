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
 ; Giving c, 3
mov [ebp - 12], dword 3
 ; Giving d, 4
mov [ebp - 16], dword 4
 ; Adding c into d
 ; Just directly get address
 ; Giving d, eax
 ; Initializing new register for private  variable d
mov eax, [ebp - 16]
add eax, [ebp - 12]
 ; Dividing b into d
 ; d has already a register to it
xchg eax, eax
cdq 
 ; Just directly get address
div dword [ebp - 8]
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
