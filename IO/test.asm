var : 
 mov [EBP - 4],  dword 1
 mov [EBP - 4],  dword 2
 add AL,   AH
 mov [EBP - 4],   [EBP - 4]
byte : 
 mov [EBP - 4],  dword 1
 mov [EBP - 4],  dword 2
 add BL,   BH
 mov [EBP - 4],   [EBP - 4]
 jnl CL,   CH
 jng DL,   AL
 sub AH,   BL
 jne BH,   CL
 sub CH,   DL
 ret 1
