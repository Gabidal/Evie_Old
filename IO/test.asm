 ; Function Feed_Foward
Feed_Foward: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 8

 ; Giving current, 0
mov [ebp - 4], dword 0
 ; Giving next, 1
mov [ebp - 8], dword 1
while0: 
 ; Comparing current and s
 ; Just directly get address of s
 ; Giving current, eax
mov eax, [ebp - 4]
cmp eax, [ebp + 12]
 ; Jumping source: '<='
jnle while0END
 ; Pointer to pointer directionation
 ; From W added address by value of current
 ; Giving W, ebx
mov ebx, [ebp + 8]
 ; current has already a register to it
lea esi, [ebx + (eax) * 4]
 ; From N added address by value of current
 ; Giving N, ecx
mov ecx, [ebp + 4]
 ; current has already a register to it
lea edi, [ecx + (eax) * 4]
 ; Giving , edx
mov edx, [edi]
imul edx, [esi]
 ; Saving  into N
 ;  has already a register to it
 ; Giving next, eax
 ; Initializing new register for private  variable next
mov eax, [ebp - 8]
mov [edi + (eax) * 4], dword edx
 ; Saving next into current
 ; next has already a register to it
mov [ebp - 4], dword eax
 ; Direct addition
add [ebp - 8], dword 1
jmp while0

while0END: 
 ; Return N
 ; Giving Returning address, ebx
mov eax, dword [ebp + 4]
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Calling Feed_Foward
call Feed_Foward

section .bss
section .data
