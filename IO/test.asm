var:
add 1, dword 2
mov [EBP - 4], dword 1
jne AL, dword 3
ret 1
je AH, dword 3
ret 0
main:
