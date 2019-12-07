section .bss
section .code
 ; Function move
move: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Pointer to pointer directionation
 ; From y added address by value of 0
 ; Adding the offset of y by 0
lea esi, [(ebp + 8) + 0 * 4]
 ; From x added address by value of 0
 ; Adding the offset of x by 0
lea edi, [(ebp + 4) + 0 * 4]
 ; Saving the value from y offsetted by 0
mov ecx, [ebp + 12]
repz movsd
 ; Return x
 ; Giving Returning address, eax
 ; Giving x, ebx
 ; Initializing new register for private  variable x
mov ebx, [ebp + 4]
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
 ; Calling move
 ; Pushing Variable 
push [ebp - 4]
 ; Pushing Variable 
push [ebp - 8]
push 5
call move

 ; Clearing the parameters
add esp, 12
 ; Giving a the return value
pop dword [ebp - 4]

 ; Return a
 ; Giving Returning address, ecx
 ; Giving a, edx
 ; Initializing new register for private  variable a
mov edx, [ebp - 4]
mov esp, ebp
pop ebp
pop ecx
push edx
jmp ecx

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

