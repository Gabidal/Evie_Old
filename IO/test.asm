global main
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Direct addition
 ; Giving 12, eax
 ; Initializing new register for number 12
mov eax, 12
add eax, dword 2
 ; Direct multiplying
 ; 12 has already a register to it
imul eax, 4
 ; Direct substraction
 ; 12 has already a register to it
sub eax, dword 5
mov [ebp - 4], eax
 ; Return d
 ; Giving Returning address, edx
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
