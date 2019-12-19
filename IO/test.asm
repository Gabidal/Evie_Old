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
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 16

 ; Allocating new memory space for new type 
push 12
call malloc
 ; Saving a into a
 ; a has already a register to it
mov [ebp - 8], dword eax
 ; Pointer address value to variable
 ; From a added address by value of 0
 ; Adding the offset of a by 0
mov esi, [eax + 0 * 4]
 ; Saving the value from a offsetted by 0
mov [ebp - 4], dword esi

 ; Return b
 ; Giving Returning address, eax
mov eax, dword [ebp - 4]
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
