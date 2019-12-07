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
 ; From b added address by value of a
 ; Add the origin of b
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp - 4]
add eax, 8
push ebp
sub ebp, eax
 ; Giving b, ebx
mov ebx, [ebp]
 ; Fixing Base Pointer
pop ebp

 ; Saving the value from b offsetted by a
 ; Giving b, ecx
 ; Initializing new register for private  variable b
 ; Add the origin of b
 ; Giving a, edx
 ; Initializing new register for private  variable a
mov edx, [ebp - 4]
add edx, 8
push ebp
sub ebp, edx
lea ecx, [ebp]
 ; Initializing new register for array variable b
pop ebp

 ; Externally adding the offset of the ofsetter variable to b
mov [ecx], ebx

 ; Return b
 ; Giving Returning address, esi
 ; Giving b, edi
 ; Initializing new register for private  variable b
mov edi, [ebp - 8]
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

