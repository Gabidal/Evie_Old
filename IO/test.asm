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
 ; Return k
 ; Giving Returning address, ebx
mov eax, dword [ebp - 4]
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function banana
banana: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Multiplying y into y
 ; Giving y, ecx
 ; Initializing new register for private  variable y
mov ecx, [ebp + 12]
imul ecx, ecx
 ; Return x
 ; Giving Returning address, edx
mov eax, dword [ebp + 8]
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
 ; Giving a, eax
 ; Initializing new register for public variable a
mov eax, [a]
add eax, [b]
 ; Calling banana
 ; Pushing Variable 
push dword [b]
 ; Pushing Variable 
 ; a has already a register to it
push eax
call banana

 ; Clearing the parameters
add esp, 8
 ; Giving c the return value
mov [ebp - 4], eax

if0: 
 ; Comparing d and 2
 ; Just directly get name of the number
 ; Giving 2, ebx
mov ebx, 2
cmp [ebp - 8], ebx
 ; Jumping source: '=='
jne if0END
 ; Return 1
 ; Giving Returning address, ecx
mov eax, dword [ebp - 4]
mov esp, ebp
pop ebp
ret 

if0END: 
jmp else1END

else1: 
 ; Return 2
 ; Giving Returning address, edx
mov eax, ebx
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
