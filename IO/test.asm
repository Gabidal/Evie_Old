section .bss
a resd 1
b resd 1
section .code
banana: 
push ebp
mov ebp, esp

sub esp, 0

mov esp, ebp
pop ebp
ret

mov [a], dword 0
mov [b], dword 1
main: 
push ebp
mov ebp, esp

sub esp, 0

mov esp, ebp
pop ebp
ret

