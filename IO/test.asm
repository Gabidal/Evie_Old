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

 ; Return 0
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
