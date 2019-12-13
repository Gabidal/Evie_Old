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
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, eax
mov eax, [ebp - 4]
cmp eax, [ebp - 8]
 ; Jumping source: '!='
je while0END
if1: 
 ; Comparing a and b
 ; Just directly get address of b
cmp eax, [ebp - 8]
 ; Jumping source: '<'
jge if1END
 ; Direct addition
add [ebp - 4], dword 1
if1END: 
if2: 
 ; Comparing a and b
 ; Just directly get address of b
cmp eax, [ebp - 8]
 ; Jumping source: '>'
jle if2END
 ; Direct substraction
sub [ebp - 4], dword 1
if2END: 
jmp while0

while0END: 
 ; Return a
 ; Giving Returning address, ebx
 ; a has already a register to it
mov esp, ebp
pop ebp
pop ebx
push eax
jmp ebx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
