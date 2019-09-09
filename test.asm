

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

global _start
_start:
call function_main
mov eax, 1
mov ebx, 0
int 80h

GASCode:


;usr:: std library functions.
function_gout:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov eax , [ebp+8]
 mov [gout.name], eax 

 ;usr:: get the string length

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
 mov ecx , [ebp+8]
 mov [gin.name], ecx 

 ;The inital destination
 push gin.getLenght
 
 ;Functions Parameters
 push dword [gin.name]
 
 ;Call the function
 call function_size
 pop edx 

 ;Get the destination to: edi 
 pop edi 
 mov [edi ], edx 


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


;usr:: std library functions.

;usr:: make a string.

;usr:: make main.
function_main:
 ;making a function stack frame
 push ebp
 mov ebp, esp


 ;usr:: print string abc.
 ;Functions Parameters
 push abc
 
 ;Call the function
 call function_gout

 ;The inital destination
 push a
 

 ;Math do: *
 mov eax , dword [a]
 imul eax , eax 


 ;Get the destination to: esi 
 pop esi 
 mov [esi ], eax 


 ;The inital destination
 push b
 

 ;Math do: *
 mov ebx , dword [b]
 imul ebx , ebx 


 ;Get the destination to: edi 
 pop edi 
 mov [edi ], ebx 


 ;The inital destination
 push c
 

 ;Math do: +
 mov ecx , dword [b]
 mov edx , dword [a]
 add edx , ecx 


 ;Get the destination to: esi 
 pop esi 
 mov [esi ], edx 

 mov eax , dword [a]
 cmp eax , ecx 
 jne else11

  ;making a stack frame start
  push ebp
  mov ebp, esp


  ;The inital destination
  push c
  

  ;Math do: +
  mov ebx , dword [c]
  add ebx , ecx 


  ;Get the destination to: edi 
  pop edi 
  mov [edi ], ebx 


  ;making a stack frame end
  mov esp, ebp
  pop ebp

 jmp end11
 else11:

  ;making a stack frame start
  push ebp
  mov ebp, esp


  ;The inital destination
  push c
  

  ;Math do: +
  mov ecx , dword [c]
  add ecx , eax 


  ;Get the destination to: esi 
  pop esi 
  mov [esi ], ecx 


  ;making a stack frame end
  mov esp, ebp
  pop ebp
 end11:


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
a dd 2
b dd 2
c dd 0


section .bss

