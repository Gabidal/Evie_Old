section .bss
_NULL_ resd 1
true resd 1
false resd 1
section .code
main: 
push ebp
mov ebp, esp

sub esp, 0

mov esp, ebp
pop ebp
ret

