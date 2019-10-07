

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
  push dword [esp+20]
  push dword 0
  mov eax, 0x5a
  mov ebx, esp
  int 0x80
  add esp, 24
  pop ebx
  push eax
jmp ebx

function_char:
  pop edi
  pop eax
  printRAX:
    lea ecx, [char.s]
    mov ebx, 10
    mov [ecx], ebx
    inc ecx
    mov [char.i], ecx
  charLoop:
    mov edx, 0
    mov ebx, 10
    div ebx
    push eax
    add edx, 48
    mov ecx, [char.i]
    mov [ecx], dl
    inc ecx
    mov [char.i], ecx
    pop eax
    cmp eax, 0
    jne charLoop
  push char.s
jmp edi

function_num:
  pop edx
  pop eax
  mov ecx, 48
  sub eax, ecx
  push eax
  jmp edx

function_reverse:
  push ebp
  mov ebp, esp
  mov esi, [ebp+8]
  push esi
  call function_size
  pop ecx
  mov eax, esi
  add eax, ecx
  mov edi, eax
  dec edi       ; edi points to end of string
  shr ecx, 1    ; ecx is count (length/2)
  jz reverse.done
  reverseLoop:
  mov al, [esi] ; load characters
  mov bl, [edi]
  mov [esi], bl ; and swap
  mov [edi], al
  inc esi       ; adjust pointers
  dec edi
  dec ecx       ; and loop
  jnz reverseLoop
  reverse.done:
  mov esp, ebp
  pop ebp
  ret

global _start
_start:
call function_main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

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
  mov esi , [ebp + 8]
  
  ;aa is now an Variable.
  mov edx , [ebp +12]
  mov [init.aa], edx 
  
  ;bb is now an Variable.
  mov eax , [ebp +16]
  mov [init.bb], eax 

  ;The inital destination
  lea edi , [esi + 4]
  push edi 
  

  ;Get the destination to: esi 
  pop esi 
  mov [esi ], edx 


  ;The inital destination
  mov esi , [ebp + 8]
  lea edi , [esi + 0]
  push edi 
  
  mov ecx , dword [init.aa]
  mov ebx , dword [eax  + ecx ]

  ;Get the destination to: edi 
  pop edi 
  mov [edi ], ebx 


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



section .data

char.i dd 0
char.s dd 0
reverse.s dd 0

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
main.apple dd 0


section .bss

