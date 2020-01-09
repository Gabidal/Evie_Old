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
 ; Adding b into a
 ; Just directly get address
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp - 4]
add eax, [ebp - 8]
 ; Saving a into c
 ; a has already a register to it
mov [ebp - 12], dword eax
if0: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, eax
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
jne  if1
 ; Return a
mov esp, ebp
pop ebp
ret 

jmp else2END
if0END: 
if1: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, eax
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
jnl  else2
 ; Return b
mov eax, dword [ebp - 8]
mov esp, ebp
pop ebp
ret 

if1END: 
jmp else2END
else2: 
 ; Return c
mov eax, dword [ebp - 12]
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
