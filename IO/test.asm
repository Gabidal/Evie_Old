section .bss
section .code
 ; Function move
move: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Pointer to pointer directionation
 ; From y added address by value of 0
 ; Giving y, eax
mov eax, [ebp + 8]
 ; Adding the offset of y by 0
lea esi, [eax + 0 * 4]
 ; From x added address by value of 0
 ; Giving x, ebx
mov ebx, [ebp + 4]
 ; Adding the offset of x by 0
lea edi, [ebx + 0 * 4]
 ; Saving the value from y offsetted by 0
mov ecx, [ebp + 12]
repz movsd
 ; Return x
 ; Giving Returning address, ecx
 ; x has already a register to it
mov esp, ebp
pop ebp
pop ecx
push ebx
jmp ecx

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
 ; Clearing the parameters
add esp, 12
 ; Giving a the return value
 ; Giving a, edx
mov edx, [ebp - 4]
 ; Adding the offset of a by 30
pop dword [edx + 30 * 4]

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

