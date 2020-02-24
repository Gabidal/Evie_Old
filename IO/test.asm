var: 
mov EAX , dword 1
mov [EBP  - 4],  dword EAX 
mov EBX , dword 2
mov [EBP  - 4],  dword EBX 
add AL ,  AH 
mov BL , 
mov [EBP  - 4],  BL 
if2: 
cmpBL ,  BH 
jnl if2END
ret EAX 
if2END: 
