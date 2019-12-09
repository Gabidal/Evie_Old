section .code ; Function sum
sum: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 4

 ; Giving i, 0
mov [ebp - 4], dword 0
while0: 
 ; Just directly get name of the number
 ; Giving 0, eax
mov eax, 0
 ; Giving x, ebx
mov ebx, [ebp + 4]
 ; Giving i, ecx
 ; Initializing new register for private  variable i
mov ecx, [ebp - 4]
cmp [ebx + (ecx) * 4], eax
je while0END
 ; Just directly get name of the number
 ; Giving y, edx
mov edx, [ebp + 8]
 ; i has already a register to it
cmp [edx + (ecx) * 4], eax
je while0END
 ; Direct addition
 ; y has already a register to it
add edx, 0
 ; Pointer to pointer directionation
 ; From x added address by value of i
 ; i has already a register to it
lea esi, [edx + (ecx) * 4]
 ; From x added address by value of i
 ; i has already a register to it
lea edi, [edx + (ecx) * 4]
 ; Saving the value from x offsetted by i
movsd
 ; Direct addition
 ; Giving i, eax
 ; Initializing new register for private  variable i
mov eax, [ebp - 4]
add eax, 1
 ; Saving i into i
 ; i has already a register to it
mov [ebp - 4], dword eax
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
sub esp, 16

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 2
mov [ebp - 8], dword 2
 ; Giving c, 3
mov [ebp - 12], dword 3
 ; Calling sum
 ; Pushing pointter 
 ; Giving b, ebx
lea ebx, [ebp - 8]
push ebx
 ; Pushing pointter 
 ; Giving c, ecx
lea ecx, [ebp - 12]
push ecx
call sum

 ; Giving a, 3
mov [ebp - 4], dword 3
 ; Return a
 ; Giving Returning address, edx
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp - 4]
mov esp, ebp
pop ebp
pop edx
push eax
jmp edx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
