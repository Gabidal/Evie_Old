raw_print: 
pop edx
pop ecx
mov ebx, 1
mov eax, 4
int 80h
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Making space for local variables 
sub esp, 4

 ; Giving a, 3
mov [ebp - 4], dword 3
 ; Return a
 ; Giving Returning address, eax
mov eax, [ebp - 4]
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
