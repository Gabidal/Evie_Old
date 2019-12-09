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
 ; Giving x, eax
mov eax, [ebp + 4]
 ; Giving i, ebx
 ; Initializing new register for private  variable i
mov ebx, [ebp - 4]
cmp [eax + (ebx) * 4], 0
je while0END
 ; Just directly get name of the number
 ; Giving y, ecx
mov ecx, [ebp + 8]
 ; Giving i, edx
 ; Initializing new register for private  variable i
mov edx, [ebp - 4]
cmp [ecx + (edx) * 4], 0
je while0END
 ; Direct addition
 ; Giving x, eax
 ; Initializing new register for private  variable x
mov eax, [ebp + 4]
add eax, 0
 ; Pointer to pointer directionation
 ; From x added address by value of i
mov eax, [ebp + 4]
 ; Giving i, ebx
 ; Initializing new register for private  variable i
mov ebx, [ebp - 4]
lea esi, [eax + (ebx) * 4]
 ; From x added address by value of i
mov eax, [ebp + 4]
 ; i has already a register to it
lea edi, [eax + (ebx) * 4]
 ; Saving the value from x offsetted by i
movsd
 ; Direct addition
 ; Giving i, ecx
 ; Initializing new register for private  variable i
mov ecx, [ebp - 4]
add ecx, 1
 ; Saving i into i
 ; i has already a register to it
mov [ebp - 4], dword ecx
jmp while0

while0END: 
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Calling sum
call sum

section .bss
