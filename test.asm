

section .text

global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

 gout:
push ebp
mov ebp, esp
sub esp, 2
;name is now Variable.
mov eax , [ebp+8]
mov [ gout.name], eax 
;size is now Variable.
mov ebx , [ebp+12]
mov [ gout.size], ebx 
push eax
mov eax,  .nullnullTokennullnull
mov ebx,  .nullnullTokennullnull
mov ecx, gout.name
mov edx, gout.size
int 80h
mov [carry], eax
pop eax
mov esp, ebp
pop ebp
ret

 gin:
push ebp
mov ebp, esp
sub esp, 2
;name is now Variable.
mov ecx , [ebp+8]
mov [ gin.name], ecx 
;size is now Variable.
mov edx , [ebp+12]
mov [ gin.size], edx 
push eax
mov eax,  .nullnullTokennullnull
mov ebx,  .nullnullTokennullnull
mov ecx, gin.name
mov edx, gin.size
int 80h
mov [carry], eax
pop eax
mov esp, ebp
pop ebp
ret

 file.open:
push ebp
mov ebp, esp
sub esp, 1
;name is now Variable.
mov eax , [ebp+8]
mov [ file.open.name], eax 
push eax
mov eax,  .nullnullTokennullnull
mov ebx, file.open.name
mov ecx,  .nullnullTokennullnull
mov edx,  .nullnullTokennullnull
int 80h
mov [header], eax
pop eax
mov esp, ebp
pop ebp
ret

 file.make:
push ebp
mov ebp, esp
sub esp, 1
;name is now Variable.
mov ebx , [ebp+8]
mov [ file.make.name], ebx 
push eax
mov eax,  .nullnullTokennullnull
mov ebx, file.make.name
mov ecx,  .nullnullTokennullnull
mov edx,  .nullnullTokennullnull
int 80h
mov [header], eax
pop eax
mov esp, ebp
pop ebp
ret

 file.close:
push ebp
mov ebp, esp
sub esp, 0
push eax
mov eax,  .nullnullTokennullnull
mov ebx, header
mov ecx,  .nullnullTokennullnull
mov edx,  .nullnullTokennullnull
int 80h
mov [header], eax
pop eax
mov esp, ebp
pop ebp
ret

 file.write:
push ebp
mov ebp, esp
sub esp, 2
;text is now Variable.
mov ecx , [ebp+8]
mov [ file.write.text], ecx 
;size is now Variable.
mov edx , [ebp+12]
mov [ file.write.size], edx 
push eax
mov eax,  .nullnullTokennullnull
mov ebx,  .nullnullTokennullnull
mov ecx, file.write.text
mov edx, file.write.size
int 80h
mov [carry], eax
pop eax
mov esp, ebp
pop ebp
ret

 file.read:
push ebp
mov ebp, esp
sub esp, 2
;name is now Variable.
mov eax , [ebp+8]
mov [ file.read.name], eax 
;size is now Variable.
mov ebx , [ebp+12]
mov [ file.read.size], ebx 
push eax
mov eax,  .nullnullTokennullnull
mov ebx, header
mov ecx, file.read.name
mov edx, file.read.size
int 80h
mov [carry], eax
pop eax
mov esp, ebp
pop ebp
ret

 main:
push ebp
mov ebp, esp
sub esp, 0
push dword [a]
mov ecx , dword [a]
imul ecx , ecx 

pop esi 
mov [esi ], ecx 
mov esp, ebp
pop ebp
ret



section .data

return dd 0
header dd 0
carry dd 0
true dd 1
false dd 0
 gout.name dd 0
 gout.size dd 0
 gin.name dd 0
 gin.size dd 0
 file.open.name dd 0
 file.make.name dd 0
 file.write.text dd 0
 file.write.size dd 0
 file.read.name dd 0
 file.read.size dd 0
a dd 1
b dd 2
c dd 3


section .bss

