

section .text

global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

 sum:
 ;making a function stack frame
 push ebp
 mov ebp, esp
 sub esp, 8
 
 ;x is now an Variable.
 mov eax , [ebp+8]
 mov [ sum.x], eax 
 
 ;y is now an Variable.
 mov ebx , [ebp+12]
 mov [ sum.y], ebx 

 ;The inital destination
 push sum.z
 

 ;Math do: +
 add eax , ebx 


 ;Get the destination to: esi 
 pop esi 
 mov [esi ], eax 

 ;returning from stack frame
 mov esp, ebp
 pop ebp

 ;returning a value from function
pop eax
add esp, 8
push dword [sum.z]
jmp eax


 main:
;making a function stack frame
push ebp
mov ebp, esp

;The inital destination
push a

;Functions Parameters
push dword [b]
push dword [a]

;Call the function
call sum

;Math do: +
mov ecx , dword [b]
pop edx 
add edx , ecx 


;Get the destination to: edi 
pop edi 
mov [edi ], edx 


;making a stack frame end
mov esp, ebp
pop ebp
ret



section .data

a dd 1
b dd 2
 sum.x dd 0
 sum.y dd 0
sum.z dd 0


section .bss

