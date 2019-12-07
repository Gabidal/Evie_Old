section .bss
section .code
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 8

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 2
mov [ebp - 8], dword 2
 ; Pointer to pointer directionation
 ; From b added address by value of 0
 ; Adding the offset of b by 0
lea esi, [(ebp - 8) + 0 * 4]
 ; From a added address by value of 0
 ; Adding the offset of a by 0
lea edi, [(ebp - 4) + 0 * 4]
 ; Saving the value from b offsetted by 0
mov ecx, [ebp - 8]
repz movsd
 ; Return a
 ; Giving Returning address, eax
 ; Giving a, ebx
 ; Initializing new register for private  variable a
mov ebx, [ebp - 4]
mov esp, ebp
pop ebp
pop eax
push ebx
jmp eax

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

