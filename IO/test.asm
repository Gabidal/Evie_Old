section .bss
true resd 1
section .code
 ; Function std_init
std_init: 
 ; Making stack frame 
push ebp
mov ebp, esp

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
sub esp, 4

 ; Calling std_init
call std_init

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Pointer to pointer directionation
 ; From true added address by value of a
 ; Giving a, eax
 ; Initializing new register for private  variable a
mov eax, [ebp - 4]
lea esi, [(true) + (eax) * 4]
 ; From true added address by value of a
 ; Giving a, ebx
 ; Initializing new register for private  variable a
mov ebx, [ebp - 4]
lea edi, [(true) + (ebx) * 4]
 ; Saving the value from true offsetted by a
movsd
 ; Return true
 ; Giving Returning address, ecx
mov esp, ebp
pop ebp
pop ecx
push dword [true]
jmp ecx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

