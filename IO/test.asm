 ; Function sum
sum: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 4

 ; Giving i, 0
mov [ebp - 4], dword 0
while0: 
 ; Comparing x and 0
 ; Just directly get name of the number
 ; Giving 0, eax
mov eax, 0
 ; Giving x, ebx
mov ebx, [ebp + 4]
 ; Giving i, ecx
 ; Initializing new register for private  variable i
mov ecx, [ebp - 4]
cmp [ebx + (ecx) * 4], eax
 ; Jumping source: '!='
je while0END
 ; Comparing y and 0
 ; Just directly get name of the number
 ; Giving y, edx
mov edx, [ebp + 8]
 ; i has already a register to it
cmp [edx + (ecx) * 4], eax
 ; Jumping source: '!='
je while0END
 ; Pointer to pointer directionation
 ; From x added address by value of i
 ; i has already a register to it
lea esi, [ebx + (ecx) * 4]
 ; From y added address by value of i
 ; i has already a register to it
lea edi, [edx + (ecx) * 4]
 ; Giving , eax
mov eax, [edi]
add eax, [esi]
 ; Saving  into y
 ;  has already a register to it
 ; i has already a register to it
mov [edi + (ecx) * 4], dword eax
 ; Direct addition
add [ebp - 4], dword 1
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
sub esp, 12

 ; Giving a, 1234567890
mov [ebp - 4], dword 1234567890
 ; Giving b, 9876543210
mov [ebp - 8], dword 9876543210
 ; Calling sum
 ; Pushing pointter 
 ; Giving a, ebx
lea ebx, [ebp - 4]
push ebx
 ; Pushing pointter 
 ; Giving b, ecx
lea ecx, [ebp - 8]
push ecx
call sum

 ; Return a
 ; Giving Returning address, edx
mov eax, [ebp - 4]
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Calling main
call main

section .bss
section .data
