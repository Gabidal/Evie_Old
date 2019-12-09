 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 8

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 4
mov [ebp - 8], dword 4
while0: 
 ; Just directly get address
 ; Giving a, eax
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
je while0END
if1: 
 ; Just directly get address
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
jge if1END
 ; Direct addition
 ; a has already a register to it
add eax, 1
 ; Saving a into a
 ; a has already a register to it
mov [ebp - 4], dword eax
if2: 
 ; Just directly get address
 ; Giving a, ebx
mov ebx, [ebp - 4]
cmp ebx, [ebp - 8]
jle if2END
 ; Direct substraction
 ; a has already a register to it
sub ebx, 1
 ; Saving a into a
 ; a has already a register to it
mov [ebp - 4], dword ebx
if2END: 
if1END: 
jmp while0

while0END: 
 ; Return a
 ; Giving Returning address, ecx
 ; a has already a register to it
mov esp, ebp
pop ebp
pop ecx
push ebx
jmp ecx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
