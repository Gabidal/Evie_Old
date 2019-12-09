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
 ; Initializing new register for private  variable x
mov eax, [ebp + 4]
cmp eax, 0
je while0END
 ; Just directly get name of the number
 ; Giving y, ebx
 ; Initializing new register for private  variable y
mov ebx, [ebp + 8]
cmp ebx, 0
je while0END
 ; Direct addition
 ; Giving x, ecx
 ; Initializing new register for private  variable x
mov ecx, [ebp + 4]
add ecx, 0
 ; Pointer to pointer directionation
 ; From x added address by value of i
mov ecx, [ebp + 4]
 ; Giving i, edx
 ; Initializing new register for private  variable i
mov edx, [ebp - 4]
lea esi, [ecx + (edx) * 4]
 ; From x added address by value of i
mov ecx, [ebp + 4]
 ; i has already a register to it
lea edi, [ecx + (edx) * 4]
 ; Saving the value from x offsetted by i
movsd
 ; Direct addition
 ; Giving i, esi
 ; Initializing new register for private  variable i
mov esi, [ebp - 4]
add esi, 1
 ; Saving i into i
 ; i has already a register to it
mov [ebp - 4], dword esi
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
