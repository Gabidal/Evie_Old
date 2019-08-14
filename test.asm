

section .text

global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

section .code
gout:
push ebp
mov ebp, esp
sub esp, 8
;size is now a variable.
mov eax , [ebp+8]
mov [gout.size], eax 
;name is now a variable.
mov ebx , [ebp+12]
mov [gout.name], ebx 
push eax
mov eax, 4
mov ebx, 1
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
sub esp, 8
;size is now a variable.
mov ecx , [ebp+8]
mov [gin.size], ecx 
;name is now a variable.
mov edx , [ebp+12]
mov [gin.name], edx 
push eax
mov eax, 3
mov ebx, 2
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
sub esp, 4
;name is now a variable.
mov eax , [ebp+8]
mov [file.open.name], eax 
push eax
mov eax, 5
mov ebx, file.open.name
mov ecx, 0
mov edx, 0777
int 80h
mov [header], eax
pop eax
mov esp, ebp
pop ebp
ret

file.make:
push ebp
mov ebp, esp
sub esp, 4
;name is now a variable.
mov ebx , [ebp+8]
mov [file.make.name], ebx 
push eax
mov eax, 8
mov ebx, file.make.name
mov ecx, 0777
mov edx, 0
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
mov eax, 6
mov ebx, header
mov ecx, 0
mov edx, 0
int 80h
mov [header], eax
pop eax
mov esp, ebp
pop ebp
ret

file.write:
push ebp
mov ebp, esp
sub esp, 8
;size is now a variable.
mov ecx , [ebp+8]
mov [file.write.size], ecx 
;text is now a variable.
mov edx , [ebp+12]
mov [file.write.text], edx 
push eax
mov eax, 4
mov ebx, 1
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
sub esp, 8
;size is now a variable.
mov eax , [ebp+8]
mov [file.read.size], eax 
;name is now a variable.
mov ebx , [ebp+12]
mov [file.read.name], ebx 
push eax
mov eax, 3
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
lea esi, [fileName]
push esi
lea esi, [fileName.size]
push esi
call gin
lea esi, [fileName]
push esi
call file.open
lea esi, [buffer]
push esi
lea esi, [buffer.size]
push esi
call file.read
call file.close
lea esi, [buffer]
push esi
lea esi, [buffer.size]
push esi
call gout
mov esp, ebp
pop ebp
ret



section .data

return dd 0
header dd 0
carry dd 0
gout.size dd 0
gout.name dd 0
gin.size dd 0
gin.name dd 0
file.open.name dd 0
file.make.name dd 0
file.write.size dd 0
file.write.text dd 0
file.read.size dd 0
file.read.name dd 0
x dd 1
y dd 5
z dd 10
one dd 1
fileName.size dd 128
buffer.size dd 256


section .bss

fileName resb 128
buffer resb 256
