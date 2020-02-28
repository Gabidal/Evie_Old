global main
char: 
banana: 
mov [EBP  - 2], byte 1
main: 
push word [EBP  - 2]
pop word [EBP  - 2]
mov AX , word [EBP  + 12]

shl AX , byte 2
mov [EBP  + 12], AX 
mov CX , AX 

imul AX , AX 
; The Left Side in - has already initialized.
sub AX , word [EBP  + 14]
mov [EBP  - 2], AX 
mov AX , word [EBP  - 2]

ret 
