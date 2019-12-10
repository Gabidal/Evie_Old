 ; Function move
move: 
 ; Making stack frame 
push ebp
mov ebp, esp

while0: 
 ; Just directly get name of the number
 ; Giving 0, eax
mov eax, 0
cmp [ebp + 12], eax
jle while0END
 ; Pointer to pointer directionation
 ; From y added address by value of s
 ; Giving y, ebx
mov ebx, [ebp + 8]
 ; Giving s, ecx
 ; Initializing new register for private  variable s
mov ecx, [ebp + 12]
lea esi, [ebx + (ecx) * 4]
 ; From x added address by value of s
 ; Giving x, edx
mov edx, [ebp + 4]
 ; s has already a register to it
lea edi, [edx + (ecx) * 4]
 ; Saving the value from y offsetted by s
movsd
 ; Direct addition
 ; Giving s, eax
 ; Initializing new register for private  variable s
mov eax, [ebp + 12]
add eax, 1
 ; Saving s into s
 ; s has already a register to it
mov [ebp + 12], dword eax
jmp while0

while0END: 
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

 ; Making space for local variables 
sub esp, 8

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 4
mov [ebp - 8], dword 4
 ; Calling move
 ; Pushing pointter 
 ; Giving a, ebx
lea ebx, [ebp - 4]
push ebx
 ; Pushing pointter 
 ; Giving b, ecx
lea ecx, [ebp - 8]
push ecx
push 1
call move

while0: 
 ; Just directly get address
 ; Giving a, edx
mov edx, [ebp - 4]
cmp edx, [ebp - 8]
je while0END
if1: 
 ; Just directly get address
mov edx, [ebp - 4]
cmp edx, [ebp - 8]
jge else2
 ; Direct addition
 ; a has already a register to it
add edx, 1
 ; Saving a into a
 ; a has already a register to it
mov [ebp - 4], dword edx
jmp else2END

else2: 
 ; Direct addition
 ; Giving b, eax
 ; Initializing new register for private  variable b
mov eax, [ebp - 8]
add eax, 1
 ; Saving b into b
 ; b has already a register to it
mov [ebp - 8], dword eax
else2END: 
if1END: 
if3: 
 ; There is already register for it, use it
cmp [ebp - 4], eax

jle else4
 ; Direct substraction
 ; a has already a register to it
sub edx, 1
 ; Saving a into a
 ; a has already a register to it
mov [ebp - 4], dword edx
jmp else4END

else4: 
 ; Direct substraction
 ; b has already a register to it
sub eax, 1
 ; Saving b into b
 ; b has already a register to it
mov [ebp - 8], dword eax
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
push edx
jmp ebx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
