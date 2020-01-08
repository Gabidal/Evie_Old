global main
 ; Function banana
banana: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Adding y into x
 ; Just directly get address
 ; Giving x, eax
 ; Initializing new register for private  variable x
mov eax, [ebp + 8]
add eax, [ebp + 12]
 ; Saving x into z
 ; x has already a register to it
mov [ebp - 4], dword eax
 ; Return z
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

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 2
mov [ebp - 8], dword 2
if0: 
 ; Saving b into a
 ; Giving b, eax
 ; Initializing new register for private  variable b
mov eax, [ebp - 8]
mov [ebp - 4], dword eax
 ; Jumping source: '<'
jge if0END
 ; Calling banana
 ; Pushing Variable 
push dword [ebp - 8]
 ; Pushing Variable 
push dword [ebp - 4]
call banana

 ; Clearing the parameters
add esp, 8
 ; Giving a the return value
 ; Giving banana, eax
mov [ebp - 4], eax

if0END: 
 ; Return a
mov eax, dword [ebp - 4]
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
