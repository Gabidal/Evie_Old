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
 ; Direct addition
 ; y has already a register to it
add edx, dword 0
 ; Pointer to pointer directionation
 ; From x added address by value of i
 ; i has already a register to it
lea esi, [edx + (ecx) * 4]
 ; From x added address by value of i
 ; i has already a register to it
lea edi, [esi + (ecx) * 4]
 ; Saving the value from x offsetted by i
movsd
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

 ; Giving b, 2
mov [ebp - 4], dword 2
 ; Giving a, 3
mov [ebp - 8], dword 3
 ; Calling sum
 ; Pushing pointter 
 ; Giving a, eax
lea eax, [ebp - 8]
push eax
 ; Pushing pointter 
 ; Giving b, ebx
lea ebx, [ebp - 4]
push ebx
call sum

 ; Return a
 ; Giving Returning address, ecx
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
