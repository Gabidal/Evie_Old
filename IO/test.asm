section .bss
section .code
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 4

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Pointer to pointer directionation
 ; From a added address by value of true
 ; Giving true, eax
 ; Initializing new register for public variable true
mov eax, dword [true]
add eax, 4
push ebp
sub ebp, eax
 ; Giving a, ebx
mov ebx, [ebp]
 ; Fixing Base Pointer
pop ebp

 ; Saving the value from a offsetted by true
 ; Giving a, ecx
 ; Initializing new register for private  variable a
 ; Giving true, edx
 ; Initializing new register for public variable true
mov edx, dword [true]
add edx, 4
push ebp
sub ebp, edx
mov ecx, [ebp]
 ; Initializing new register for array variable a
pop ebp

 ; Externally adding the offset of the ofsetter variable to a
 ; true has already a register to it
add ecx, edx
mov [ecx], ebx

 ; Return a
 ; Giving Returning address, esi
 ; Giving a, edi
 ; Initializing new register for private  variable a
mov edi, [ebp - 4]
mov esp, ebp
pop ebp
pop esi
push edi
jmp esi

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

