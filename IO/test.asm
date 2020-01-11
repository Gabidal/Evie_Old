global main
 ; Function banana
banana: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Direct addition
add [ebp + 8], dword 4
 ; Saving a into a
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp + 8]
mov [ebp + 8], dword eax
 ; Return a
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function apple
apple: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Return 4
mov eax, 4
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
 ; Direct addition
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp - 4]
add eax, dword 5
 ; Saving a into c
 ; a has already a register to it
mov [ebp - 12], dword eax
 ; Calling banana
push dword 1
call banana

 ; Clearing the parameters
add esp, 4
 ; Giving d the return value
 ; Giving banana, eax
mov [ebp - 16], eax

 ; Giving e, 4
mov [ebp - 20], dword 4
if0: 
 ; Comparing d and e
 ; Just directly get address of e
 ; Giving d, edx
mov edx, [ebp - 16]
cmp edx, [ebp - 20]
jne  if0END
 ; Return d
mov eax, edx
mov esp, ebp
pop ebp
ret 

if0END: 
if1: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, eax
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
jne  if2
 ; Return a
mov esp, ebp
pop ebp
ret 

jmp else3END
if1END: 
if2: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, eax
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
jnl  else3
 ; Return b
mov eax, dword [ebp - 8]
mov esp, ebp
pop ebp
ret 

if2END: 
jmp else3END
else3: 
 ; Return c
mov eax, dword [ebp - 12]
mov esp, ebp
pop ebp
ret 

else3END: 
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
