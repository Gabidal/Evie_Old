section .bss
true resd 1
section .code
 ; Function std_init
std_init: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
 ; Giving true, 1
mov [true], dword 1
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
 ; Giving b, 2
mov [ebp - 8], dword 2
 ; Calling std_init
call std_init

 ; Pointer to pointer directionation
 ; From true added address by value of a
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp - 4]
 ; Giving true, ebx
mov ebx, [true + eax]
 ; Saving the value from true offsetted by a
 ; Giving true, ecx
 ; Initializing new register for public variable true
 ; Giving b, edx
 ; Initializing new register for private  variable b
mov edx, [ebp - 8]
lea ecx, [true + edx]
 ; Externally adding the offset of the ofsetter variable to true
mov [ecx], ebx

 ; Return true
 ; Giving Returning address, esi
mov esp, ebp
pop ebp
pop esi
push dword [true]
jmp esi

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

