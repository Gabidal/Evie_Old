

section .text

global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

 sum:
push ebp
mov ebp, esp
sub esp, 2
;a is now Variable.
mov eax , [ebp+8]
mov [ sum.a], eax 
;b is now Variable.
mov ebx , [ebp+12]
mov [ sum.b], ebx 
push sum.a
mov ecx , dword [sum.b]
mov edx , dword [sum.a]
add edx , ecx 

pop esi 
mov [esi ], edx 
mov esp, ebp
pop ebp
pop eax
add esp, 8
push dword [sum.a]
jmp eax

 negate:
push ebp
mov ebp, esp
sub esp, 1
;a is now Variable.
mov eax , [ebp+8]
mov [ negate.a], eax 
push negate.a
mov ebx , dword [negate.a]
sub ebx , ebx 

pop edi 
mov [edi ], ebx 
mov esp, ebp
pop ebp
pop eax
add esp, 4
push dword [negate.a]
jmp eax

 main:
push ebp
mov ebp, esp
sub esp, 0
push a
pop ecx 
pop esi 
mov [esi ], ecx 
push a
pop edx 
pop edi 
mov [edi ], edx 
push a
mov eax , dword [ .nullnullTokennullnull]
pop esi 
mov [esi ], eax 


section .data

a dd 1
b dd 2
c dd 3
 sum.a dd 0
 sum.b dd 0
 negate.a dd 0


section .bss

