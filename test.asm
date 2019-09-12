

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

function_gout:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov eax , [ebp+8]
 mov [gout.name], eax 
 ;Set the value to local var
 mov dword [gout.getLenght], 0

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
 mov dword [gin.getLenght], 0

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

function_main:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 While_0:

 ;making a stack frame start
 push ebp
 mov ebp, esp

 mov ecx , dword [a]
 cmp ecx , dword [b]
 jne else11

  ;making a stack frame start
  push ebp
  mov ebp, esp


  ;The inital destination
  push a
  
  ;Functions Parameters
  push dword [a]
  
  ;Call the function
  call function_char

  pop edx 

  ;Get the destination to: esi 
  pop esi 
  mov [esi ], edx 

  ;Functions Parameters
  push dword [a]
  
  ;Call the function
  call function_reverse
  ;deleteing the parameters from stack
  add esp, 4

  ;Functions Parameters
  push dword [a]
  
  ;Call the function
  call function_gout
  ;deleteing the parameters from stack
  add esp, 4


  ;making a stack frame end
  mov esp, ebp
  pop ebp
 jmp end11
 else11:

  ;making a stack frame start
  push ebp
  mov ebp, esp


  ;The inital destination
  push b
  
  ;Functions Parameters
  push dword [b]
  
  ;Call the function
  call function_char

  pop eax 

  ;Get the destination to: edi 
  pop edi 
  mov [edi ], eax 

  ;Functions Parameters
  push dword [b]
  
  ;Call the function
  call function_reverse
  ;deleteing the parameters from stack
  add esp, 4

  ;Functions Parameters
  push dword [b]
  
  ;Call the function
  call function_gout
  ;deleteing the parameters from stack
  add esp, 4


  ;making a stack frame end
  mov esp, ebp
  pop ebp
 end11:

 ;making a stack frame end
 mov esp, ebp
 pop ebp

;cheking the while.
add dword [a], 1
cmp ecx , dword [c]
jl While_0


;making a stack frame end
mov esp, ebp
pop ebp
ret



section .data

char.i dd 0
char.s times 20 db 1
 dd 0
reverse.s times 512 db 1
 dd 0
header dd 0
carry dd 0
gout.name dd 0
gout.getLenght dd 0
gin.name dd 0
gin.getLenght dd 0
a dd 1
b dd 2
c dd 10


section .bss

