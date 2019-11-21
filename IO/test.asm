section .bss
_NULL_ resd 1
true resd 1
false resd 1
section .code
std: 
push ebp
mov ebp, esp

sub esp, 0

mov [true], dword 1
mov [false], dword 0
mov esp, ebp
pop ebp
ret

main: 
push ebp
mov ebp, esp

sub esp, 0

if0: 
mov eax, [true]
cmp eax, [true]
jne if0END
if0END: 
mov esp, ebp
pop ebp
ret

