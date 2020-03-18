global _start
_start: 
__start: 
call main
mov eax , eax 
ret
 
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 20
_while4: 
mov eax , dword [ebp  - 4]
mov ebx , dword 10
cmp eax , ebx 
jnl _while4END
mov ecx , dword [ebp  - 4]
mov edx , dword [ebp  - 20]
mov edi , dword [(ebp  - 16) + edx  * 4]
mov esi , dword [(ebp  - 20) + ecx  * 4]
imul edi , esi 
mov eax , dword [ebp  - 16]
mov ebx , dword [ebp  - 12]
mov ecx , dword [(ebp  - 8) + ebx  * 4]
mov edx , dword [(ebp  - 12) + eax  * 4]
add ecx , edx 
sub ecx , edi 
mov edi , dword [ebp  - 8]
mov dword [(ebp  - 4) + edi  * 4], ecx 
jmp _while4
_while4END: 
