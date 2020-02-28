global main
char: 
main: 
mov AX , word [EBP  + 10]

imul AX , word AX 
; The Left Side in + has already initialized.
add AX , word [EBP  + 12]
mov [EBP  - 2], word AX 
mov AX , word [EBP  - 2]

ret 
