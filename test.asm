

section .text


len:
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

alloc:
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
call main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

 gout:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov eax , [ebp+8]
 mov [ gout.name], eax 

 ;The inital destination
 push gout.getLenght
 
 ;Functions Parameters
 push dword [gout.name]
 
 ;Call the function
 call len
 pop ebx 

 ;Get the destination to: esi 
 pop esi 
 mov [esi ], ebx 


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

 gin:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov ecx , [ebp+8]
 mov [ gin.name], ecx 

 ;The inital destination
 push gin.getLenght
 
 ;Functions Parameters
 push dword [gin.name]
 
 ;Call the function
 call len

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

 file.open:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov edx , [ebp+8]
 mov [ file.open.name], edx 

 push eax
 mov eax, 5
 mov ebx, dword [file.open.name]
 mov ecx, 0
 mov edx, 0777
 int 80h
 mov [header], eax
 pop eax


 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

 file.make:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;name is now an Variable.
 mov eax , [ebp+8]
 mov [ file.make.name], eax 

 push eax
 mov eax, 8
 mov ebx, dword [file.make.name]
 mov ecx, 0777
 mov edx, 0
 int 80h
 mov [header], eax
 pop eax


 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

 file.close:
 ;making a function stack frame
 push ebp
 mov ebp, esp


 push eax
 mov eax, 6
 mov ebx, dword [header]
 mov ecx, 0
 mov edx, 0
 int 80h
 mov [header], eax
 pop eax


 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

 file.write:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 8
 
 ;text is now an Variable.
 mov ebx , [ebp+8]
 mov [ file.write.text], ebx 
 
 ;size is now an Variable.
 mov ecx , [ebp+12]
 mov [ file.write.size], ecx 

 push eax
 mov eax, 4
 mov ebx, 1
 mov ecx, dword [file.write.text]
 mov edx, dword [file.write.size]
 int 80h
 mov [carry], eax
 pop eax


 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

 file.read:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 8
 
 ;name is now an Variable.
 mov edx , [ebp+8]
 mov [ file.read.name], edx 
 
 ;size is now an Variable.
 mov eax , [ebp+12]
 mov [ file.read.size], eax 

 push eax
 mov eax, 3
 mov ebx, dword [header]
 mov ecx, dword [file.read.name]
 mov edx, dword [file.read.size]
 int 80h
 mov [carry], eax
 pop eax


 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

 main:
 ;making a function stack frame
 push ebp
 mov ebp, esp


 ;The inital destination
 push vector
 
 ;Functions Parameters
 
 ;Call the function
 call alloc
 pop ebx 

 ;Get the destination to: esi 
 pop esi 
 mov [esi ], ebx 


 ;The inital destination
 push vector
 
 mov ecx , dword [b]
 mov edx , dword [vector]
 add edx , ecx 

 ;Get the destination to: edi 
 pop edi 
 mov [edi ], edx 


 ;The inital destination
 push vector
 
 mov eax , dword [c]
 sub edx , eax 

 ;Get the destination to: esi 
 pop esi 
 mov [esi ], edx 

 ;Functions Parameters
 push vector
 
 ;Call the function
 call gout

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
 file.open.name dd 0
 file.make.name dd 0
 file.write.text dd 0
 file.write.size dd 0
 file.read.name dd 0
 file.read.size dd 0
vector dd 0
a dd 4
b dd 2
c dd 3


section .bss

