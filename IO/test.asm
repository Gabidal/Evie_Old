section .bss
section .code
 ; Function move
move: 
 ; Making stack frame 
push ebp
mov ebp, esp

while0: 
 ; Just directly get name of the number
 ; Giving s, eax
 ; Initializing new register for private  variable s
mov eax, [ebp + 12]
cmp eax, 0
jle while0END
 ; Pointer to pointer directionation
 ; From y added address by value of s
 ; Giving y, ebx
mov ebx, [ebp + 8]
 ; Giving s, ecx
 ; Initializing new register for private  variable s
mov ecx, [ebp + 12]
lea esi, [ebx + (ecx) * 4]
 ; From x added address by value of s
 ; Giving x, edx
mov edx, [ebp + 4]
 ; Giving s, esi
 ; Initializing new register for private  variable s
mov esi, [ebp + 12]
lea edi, [edx + (esi) * 4]
 ; Saving the value from y offsetted by s
movsd
 ; Direct addition
 ; Giving s, edi
 ; Initializing new register for private  variable s
mov edi, [ebp + 12]
add edi, 1
 ; Saving s into s
 ; s has already a register to it
mov [ebp + 12], dword edi
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
sub esp, 4

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Calling move
 ; Pushing pointter 
 ; Giving a, eax
lea eax, [ebp - 4]
push eax
 ; Pushing pointter 
 ; Giving b, ebx
lea ebx, [ebp - 8]
push ebx
push 10
call move

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

