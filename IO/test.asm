char: 
main: 
mov AL , byte 1

add AL , byte 2
mov [EBP  - 4], byte AL 
mov AL , byte [EBP  - 4]

ret 
