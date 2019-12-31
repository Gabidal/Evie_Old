global main
 ; Function yeet
yeet: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Direct addition
add [a], dword 1
 ; Direct addition
 ; Giving b, eax
 ; Initializing new register for public variable b
mov eax, [b]
add eax, dword 1
 ; Saving b into k
 ; b has already a register to it
mov [ebp - 4], dword eax
 ; Return k
 ; Giving Returning address, ebx
mov esp, ebp
pop ebp
ret 

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

 ; Calling yeet
call yeet

 ; Giving c the return value
mov [ebp - 4], eax

 ; Adding b into a
 ; Just directly get address
 ; Giving a, ecx
 ; Initializing new register for public variable a
mov ecx, [a]
add ecx, [b]
 ; Saving a into d
 ; a has already a register to it
mov [ebp - 8], dword ecx
if0: 
 ; Comparing d and 2
 ; Just directly get name of the number
 ; Giving 2, edx
mov edx, 2
cmp [ebp - 8], edx
 ; Jumping source: '=='
jne if0END
 ; Return 1
 ; Giving Returning address, eax
mov eax, 1
mov esp, ebp
pop ebp
ret 

if0END: 
jmp else1END

else1: 
 ; Return 2
 ; Giving Returning address, ebx
mov eax, 2
mov esp, ebp
pop ebp
ret 

else1END: 
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
