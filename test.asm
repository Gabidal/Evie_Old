

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

function_malloc:
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

function_char:
  pop edx
  pop eax
  mov ecx, 48
  add eax, ecx
  push eax
  jmp edx
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
 ;Set the value to local var
 mov ebx , 0
 mov [gout.getLenght], ebx 

 ;usr:: get the string length

 ;The inital destination
 push gout.getLenght
 
 ;Functions Parameters
 push dword [gout.name]
 
 ;Call the function
 call function_size
 pop ecx 

 ;Get the destination to: esi 
 pop esi 
 mov [esi ], ecx 


 ;usr:: call sys print

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

function_gin:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov edx , [ebp+8]
 mov [gin.name], edx 
 ;Set the value to local var
 mov eax , 0
 mov [gin.getLenght], eax 

 ;The inital destination
 push gin.getLenght
 
 ;Functions Parameters
 push dword [gin.name]
 
 ;Call the function
 call function_size
 pop ebx 

 ;Get the destination to: edi 
 pop edi 
 mov [edi ], ebx 


 push eax
 mov eax, 3
 mov ebx, 2
 mov ecx, dword [gin.name]
 mov edx, dword [gin.getLenght]
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

 ;Set the value to local var
 mov ecx , 0
 mov [main.x], ecx 
 While_0:

 ;making a stack frame start
 push ebp
 mov ebp, esp

 ;Set the value to local var
 mov edx , 0
 mov [main.y], edx 
 While_1:

 ;making a stack frame start
 push ebp
 mov ebp, esp


 ;The inital destination
 push c
 
 ;Functions Parameters
 push dword [main.y]
 
 ;Call the function
 call function_char
 pop eax 

 ;Get the destination to: esi 
 pop esi 
 mov [esi ], eax 

 ;Functions Parameters
 push c
 
 ;Call the function
 call function_gout
 add esp, 4

 ;making a stack frame end
 mov esp, ebp
 pop ebp

;cheking the while.
mov eax, dword [main.y]
add eax, 1
mov [main.y], eax
cmp eax, dword [a]
jl While_1

;making a stack frame end
mov esp, ebp
pop ebp

;cheking the while.
mov eax, dword [main.x]
add eax, 1
mov [main.x], eax
cmp eax, dword [a]
jl While_0

;making a stack frame end
mov esp, ebp
pop ebp
ret



section .data

header dd 0
carry dd 0
gout.name dd 0
gout.getLenght dd 0
gin.name dd 0
gin.getLenght dd 0
abc db "moikkamoi!", 0
a dd 10
c dd 0
main.x dd 0
main.y dd 0


section .bss

