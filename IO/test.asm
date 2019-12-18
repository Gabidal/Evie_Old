malloc: 
push dword 0
push dword -1
push dword 0x22
push dword 0x03
push dword [esp + 16]
push dword 0
mov eax, 0x5a
mov ebx, esp
int 0x80
add esp, 24
ret 
 ; Function get
get: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 4

 ; Pointer address value to variable
 ; From t added address by value of o
 ; Giving t, eax
mov eax, [ebp + 4]
 ; Giving o, ebx
 ; Initializing new register for private  variable o
mov ebx, [ebp + 8]
mov esi, [eax + (ebx) * 4]
 ; Saving the value from t offsetted by o
mov [ebp - 4], dword esi

 ; Return r
 ; Giving Returning address, ecx
mov eax, [ebp - 4]
mov esp, ebp
pop ebp
ret 

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
sub esp, 20

 ; Allocating new memory space for new type 
push 12
call malloc
 ; Saving a into a
 ; a has already a register to it
mov [ebp - 8], dword eax
 ; Calling get
 ; Pushing Variable 
 ; a has already a register to it
push eax
push dword 0
call get

 ; Clearing the parameters
add esp, 8
 ; Giving b the return value
mov [ebp - 4], eax

 ; Calling get
 ; Pushing Variable 
 ; a has already a register to it
push eax
push dword 4
call get

 ; Clearing the parameters
add esp, 8
 ; Adding b into b
 ; Just directly get address
 ; get has already a register to it
add eax, [ebp - 4]
 ; Saving b into b
 ; b has already a register to it
mov [ebp - 4], dword eax
 ; Return b
 ; Giving Returning address, edx
mov eax, [ebp - 4]
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Calling main
call main

section .bss
section .data
