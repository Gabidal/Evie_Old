global main
 ; Function banana
banana: 
mov eax, 4
ret 
 ; Function apple
apple: 
mov eax, 4
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
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp + 8]
add eax, [ebp - 4]
 ; Saving a into c
 ; a has already a register to it
mov [ebp - 8], dword eax
 ; Giving d, 4
mov [ebp - 12], dword 4
 ; Giving e, 4
mov [ebp - 16], dword 4
if0: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, edx
mov edx, [ebp + 8]
cmp edx, [ebp - 4]
jne  if1
 ; Return a
mov eax, edx
mov esp, ebp
pop ebp
ret 

jmp else2END
if0END: 
if1: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, edx
mov edx, [ebp + 8]
cmp edx, [ebp - 4]
jnl  else2
 ; Return b
mov eax, dword [ebp - 4]
mov esp, ebp
pop ebp
ret 

if1END: 
jmp else2END
else2: 
 ; Return c
mov esp, ebp
pop ebp
ret 

else2END: 
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
