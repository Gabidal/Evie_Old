global main
 ; Function banana
banana: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Giving a, 4
mov [ebp - 4], dword 4
 ; Return a
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
add eax, dword 4
 ; Saving a into c
 ; a has already a register to it
mov [ebp - 12], dword eax
 ; Calling banana
call banana

 ; Giving d the return value
 ; Giving banana, eax
mov [ebp - 16], eax

if0: 
 ; Comparing d and 4
 ; Just directly get name of the number
 ; Giving 4, edx
mov edx, 4
cmp [ebp - 16], edx
jne  if0
 ; Return d
mov eax, dword [ebp - 16]
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
