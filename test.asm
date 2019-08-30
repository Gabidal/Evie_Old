

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
 ;x is now Variable.
 mov eax , [ebp+8]
 mov [ sum.x], eax 
 ;y is now Variable.
 mov ebx , [ebp+12]
 mov [ sum.y], ebx 
 cmp eax , ebx 
 jge else11
  
push ebp
  mov ebp, esp

  
mov esp, ebp
  pop ebp

pop eax
add esp, 8
push dword [sum.x]
jmp eax
 
jmp end11
 
else11: 
 
push ebp
 mov ebp, esp

 
mov esp, ebp
 pop ebp

pop eax
add esp, 8
push dword [sum.y]
jmp eax
 
end11: 

mov esp, ebp
pop ebp

ret

 main:
push ebp
mov ebp, esp

mov esp, ebp
pop ebp

ret



section .data

 sum.x dd 0
 sum.y dd 0


section .bss

