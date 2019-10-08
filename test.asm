

section .text

function_gout:
 ;making a function stack frame
 push ebp
 mov ebp, esp
 sub esp, 4
 ;[ebp +8 ]  ;gout.name
 push dword [ebp + 8]
 call function_size
 pop edx
 mov eax, 4
 mov ebx, 1
 mov ecx, [ebp + 8]
 int 80h
 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret
function_malloc:
  push dword 0
  push dword -1
  push dword 0x22
  push dword 0x03
  push dword [esp+20]
  push dword 0
  mov eax, 0x5a
  mov ebx, esp
  int 0x80
  add esp, 24
  pop ebx
  push eax
jmp ebx


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

global _start
_start:
call function_main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

function_gin:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov eax , [ebp +8]
 mov [gin.name], eax 
 ;Set the value to local var
 mov dword [gin.getLenght], 0

 ;The inital destination
 push gin.getLenght
 
 ;Functions Parameters
 push dword [gin.name]
 
 ;Call the function
 call function_size

 pop ecx 

 ;Get the destination to: esi 
 pop esi 
 mov [esi ], ecx 


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

function_exit:
 ;making a function stack frame
 push ebp
 mov ebp, esp


 push eax
 mov eax, 1
 mov ebx, 0
 mov ecx, 0
 mov edx, 0
 int 80h
 mov [carry], eax
 pop eax


 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

type_vector:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 ;Set the value to local var
 mov dword [vector.b], 1
 ;Set the value to local var
 mov dword [vector.a], 2
 function_init:
  ;making a function stack frame
  push ebp
  mov ebp, esp

  sub esp, 12
  
  ;this is CLASS address.
  mov edi , [ebp + 8]
  
  ;aa is now an Variable.
  mov ecx , [ebp +12]
  mov [init.aa], ecx 
  
  ;bb is now an Variable.
  mov edx , [ebp +16]
  mov [init.bb], edx 

  ;The inital destination
  lea esi , [edi + 4]
  push esi 
  

  ;Get the destination to: edi 
  pop edi 
  mov [edi ], ecx 


  ;The inital destination
  mov edi , [ebp + 8]
  lea esi , [edi + 0]
  push esi 
  
  mov ebx , dword [edi + 4]
  mov eax , dword [edx  + ebx ]

  ;Get the destination to: esi 
  pop esi 
  mov [esi ], eax 


  ;making a stack frame end
  mov esp, ebp
  pop ebp
 ret


;making a stack frame end
mov esp, ebp
pop ebp
ret

function_main:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 ;Set the value to local var
 mov dword [main.a], 1
 ;Set the value to local var
 mov dword [main.b], 2
 ;Give malloc Type size.
 push 8

 ;Call malloc.
 call function_malloc

 pop dword [main.apple]
 ;deleteing the parameters from stack
 add esp, 4
 ;Save new Type address in stack at(0)
 push dword [main.apple]

 ;Functions Parameters
 push main.c
 push dword [main.a]

 ;Giving the function Type address.
 push dword [main.apple]
 
 ;Call the function
 call function_init
 ;deleteing the parameters from stack
 add esp, 12

 ;Functions Parameters
 push main.d
 
 ;Call the function
 call function_gout
 ;deleteing the parameters from stack
 add esp, 4


 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret



section .data

header dd 0
carry dd 0

startVariables_gin:
gin.name dd 0
gin.getLenght dd 0
endVariables_gin:


startVariables_exit:
endVariables_exit:


vector:
vector.b dd 1
vector.a dd 2

startVariables_init:
init.aa dd 0
init.bb dd 0
endVariables_init:

vector_end:

startVariables_main:
main.a dd 1
main.b dd 2
main.c times 10 dd 0
main.d db "hello joonas!", 0
main.apple dd 0
endVariables_main:



section .bss

