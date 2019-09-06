

section .text


function_size:
pop ebx
pop edx
xor eax, eax
jmp check
top:
inc edx
inc eax
check:
cmp byte [edx], 0
jnz top
push eax
push ebx
ret

function_alloc:
push dword 0
push dword -1
push dword 0x22
push dword 0x03
push dword [esp+16]
push dword 0
mov eax, 0x5a
mov ebx, esp
int 0x80
add esp, 24
pop ebx
push eax
jmp ebx

global _start
_start:
call function_main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

function_gout:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov eax , [ebp+8]
 mov [gout.name], eax 

 ;The inital destination
 push gout.getLenght
 
 ;Functions Parameters
 push dword [gout.name]
 
 ;Call the function
 call function_size
 pop ebx 

 ;Get the destination to: esi 
 pop esi 
 mov [esi ], ebx 


 push eax
 mov eax, 4
 mov ebx, 1
 mov ecx, dword [gout.name]
 mov edx, dword [gout.getLenght]
 int 80h
 mov [carry], eax
 pop eax


 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

function_main:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 ;Functions Parameters
 push abc
 
 ;Call the function
 call function_gout

 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret



section .data

header dd 0
carry dd 0
gout.name dd 0
gout.getLenght dd 0
abc db "moikkamoi!", 0


section .bss

