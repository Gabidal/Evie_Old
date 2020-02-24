var : 
 mov [EBP - 4],  dword 1
 mov [EBP - 4],  dword 2
 add AL,   AH
 mov [EBP - 4],   [EBP - 4]
if2 : 
 cmp BL,   BH
jnl if2END 
 ret 1
if2END : 
