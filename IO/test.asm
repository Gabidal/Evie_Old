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
if0: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, eax
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
 ; Jumping source: '=='
jne if0END
 ; Return 1
mov eax, 1
mov esp, ebp
pop ebp
ret 

if0END: 
jmp if1
if1: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, eax
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
 ; Jumping source: '!='
je if1END
 ; Return 2
mov eax, 2
mov esp, ebp
pop ebp
ret 

if1END: 
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
