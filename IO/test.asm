

section .text

global _start
_start:
push dword vector
call main
mov eax, 1
mov ebx, 0
int 80h

GASCode:


main:
 ;making a function stack frame
 push ebp
 mov ebp, esp

  mov eax, dword [ebp + 8]

  mov esi, dword [eax + 4]
  mov edi, dword [eax]
  movsd

  mov eax, dword [edi]

 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

;a = b

section .data

header dd 0
carry dd 0

startVariables_gin:
gin.name dd 0
gin.getLenght dd 0
endVariables_gin:


startVariables_exit:
endVariables_exit:

banaani1 dd 123
banaani2 dd 321

vector:
vector.a dd banaani1
vector.b dd banaani2

startVariables_combine:
combine.other dd 0
endVariables_combine:

vector_end:

startVariables_main:
main.a dd 0
main.b dd 0
endVariables_main:



section .bss

