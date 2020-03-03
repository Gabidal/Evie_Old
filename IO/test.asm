global main
main: 
; The Right Side in = has already initialized.

; The Right Side in = has already initialized.

mov a, dword [EBP  - 4]
add dword [EBP  - 4], dword [EBP  - 4]
; The Right Side in = has already initialized.

mov a, dword [EBP  - 4]
ret 
