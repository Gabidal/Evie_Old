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
 ; Giving b, eax
mov eax, [ebp - 8]
 ; Adding the offset of b by 0
lea esi, [eax + 0 * 4]
 ; From a added address by value of 0
 ; Giving a, ebx
mov ebx, [ebp - 4]
 ; Adding the offset of a by 0
lea edi, [ebx + 0 * 4]
 ; Giving , ecx
ecx, [edi]
add ecx, [esi]
 ; Saving  into a
 ;  has already a register to it
mov ebx, [ebp - 4]
 ; Adding the offset of a by 0
mov [ebx + 0 * 4], dword ecx
 ; Return a
 ; Giving Returning address, edx
 ; Giving a, esi
 ; Initializing new register for private  variable a
mov esi, [ebp - 4]
mov esp, ebp
pop ebp
pop edx
push esi
jmp edx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

