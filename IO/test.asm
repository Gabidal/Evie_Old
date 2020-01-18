global main
 ; Function banana
banana: 
 ; Making stack frame 
push ebp
mov ebp, esp

if0: 
 ; Comparing a and 10
 ; Just directly get name of the number
 ; Giving 10, eax
mov eax, 10
cmp [ebp + 8], eax
jne  else1
 ; Return 4
mov eax, 4
mov esp, ebp
pop ebp
ret 

jmp else1END
if0END: 
jmp else1END
else1: 
 ; Return 3
mov eax, 3
mov esp, ebp
pop ebp
ret 

else1END: 
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

 ; Giving b, 2
mov [ebp - 4], dword 2
 ; Adding b into a
 ; Just directly get address
 ; Giving a, edx
 ; Initializing new register for private  variable a
mov edx, [ebp + 8]
add edx, [ebp - 4]
 ; Saving a into c
 ; a has already a register to it
mov [ebp - 8], dword edx
 ; Giving d, 3
mov [ebp - 12], dword 3
 ; Giving e, 4
mov [ebp - 16], dword 4
if2: 
 ; Comparing d and e
 ; Just directly get address of e
 ; Giving d, eax
mov eax, [ebp - 12]
cmp eax, [ebp - 16]
jne  if2END
 ; Return d
mov esp, ebp
pop ebp
ret 

if2END: 
if3: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, edx
mov edx, [ebp + 8]
cmp edx, [ebp - 4]
jne  if4
 ; Return a
mov eax, edx
mov esp, ebp
pop ebp
ret 

jmp else5END
if3END: 
if4: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, edx
mov edx, [ebp + 8]
cmp edx, [ebp - 4]
jnl  else5
 ; Return b
mov eax, dword [ebp - 4]
mov esp, ebp
pop ebp
ret 

if4END: 
jmp else5END
else5: 
 ; Return c
mov eax, dword [ebp - 8]
mov esp, ebp
pop ebp
ret 

else5END: 
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
