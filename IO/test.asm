global main
char: 
main: 
mov AL , byte [EBP  + 10]

add AL , byte [EBP  + 9]
mov [EBP  - 1], byte AL 
mov AL , byte [EBP  - 1]

ret 
