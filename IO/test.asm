global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

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
pop ebx
push eax
jmp ebx
section .bss
_NULL_ resd 1
true resd 1
false resd 1
section .code
init_std: 
push ebp
mov ebp, esp

sub esp, 0

mov [true], dword 1
mov [false], dword 0
mov esp, ebp
pop ebp
ret

Init_Variables_Of_raw_vector: 
push ebp
mov ebp, esp

mov esp, ebp
pop ebp
ret

vector: 
push ebp
mov ebp, esp

sub esp, 0

mov eax, [ebp + 4]
mov [eax + 0], dword 4
mov ebx, [ebp + 8]
mov ecx, [ebp + 20]
mov [ecx + 16], dword ebx
push dword 16
call malloc
pop dword [ebp - 4]
mov edx, [ebp - 4]
mov esi, [ebp + 36]
mov [esi + 32], dword edx
push dword 16
call malloc
pop dword [ebp - 20]
mov edi, [ebp - 20]
mov eax, [ebp + 52]
mov [eax + 48], dword edi
mov esp, ebp
pop ebp
ret

main: 
push ebp
mov ebp, esp

sub esp, 0

push dword 16
call malloc
pop dword [ebp - 4]
call vector

mov ebx, [ebp - 4]
mov esp, ebp
pop ebp
pop ecx
push ebx
jmp ecx

mov esp, ebp
pop ebp
ret

call main

