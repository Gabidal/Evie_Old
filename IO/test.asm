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
cmp eax, [ebp - 8]
jge else2
 ; Direct addition
add [ebp - 4], 1
jmp else2END

else2: 
 ; Direct addition
add [ebp - 8], 1
else2END: 
if1END: 
if3: 
 ; Just directly get address
cmp eax, [ebp - 8]
jle else4
 ; Direct substraction
sub [ebp - 4], 1
jmp else4END

else4: 
 ; Direct substraction
sub [ebp - 8], 1
else4END: 
if3END: 
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
