

section .text

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
 mov dword [vector.a], 2
 ;Set the value to local var
 mov dword [vector.b], 1
 function_combine:
  ;making a function stack frame
  push ebp
  mov ebp, esp

  sub esp, 8
  
  ;this is CLASS address.
  mov edi , [ebp + 8]
  
  ;other is now an Variable.
  mov ecx , [ebp +12]
  mov [combine.other], ecx 

  ;The inital destination
  lea esi , [edi + 0]
  push esi 
  
  ;Math do: +
  mov edi , [esp + 0]
  mov edx , dword [edi + 0]
  add edx , ecx 

  ;Get the destination to: esi 
  pop esi 
  mov [esi ], edx 


  ;The inital destination
  mov esi , [ebp + 8]
  lea edi , [esi + 4]
  push edi 
  
  ;Math do: +
  mov edi , [esp + 0]
  mov eax , dword [edi + 4]
  add eax , ecx 

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

 ;Give malloc Type size.
 push 8

 ;Call malloc.
 call function_malloc

 pop dword [main.a]
 ;deleteing the parameters from stack
 add esp, 4
 ;Save new Type address in stack at(0)
 push dword [main.a]

 ;Give malloc Type size.
 push 8

 ;Call malloc.
 call function_malloc

 pop dword [main.b]
 ;deleteing the parameters from stack
 add esp, 4
 ;Save new Type address in stack at(4)
 push dword [main.b]

 ;Functions Parameters
 push dword [main.b]

 ;Giving the function Type address.
 push dword [main.a]
 
 ;Call the function
 call function_combine
 ;deleteing the parameters from stack
 add esp, 8


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
vector.a dd 2
vector.b dd 1

startVariables_combine:
combine.other dd 0
endVariables_combine:

vector_end:

startVariables_main:
main.a dd 0
main.b dd 0
endVariables_main:



section .bss

