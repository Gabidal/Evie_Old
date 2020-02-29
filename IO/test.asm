global main
char: 
const: 
main: 
mov AL , [EBP  + 8]

shl AL , byte 2
mov [EBP  + 8], AL 
mov BL , AL 

imul AL , AL 
; The Left Side in - has already initialized.
sub AL , [EBP  + 8]
mov [EBP  - 0], AL 
mov AL , byte [EBP  - 0]

ret 
