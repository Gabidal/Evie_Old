var return = 0
var false = 0
var true = 1

func NAND NAND_a NAND_b 
  return = NAND_a !& NAND_b
ret

func OR OR_a OR_b
  return = OR_a || OR_b
ret

func XOR XOR_a XOR_b
  return = XOR_a !| XOR_b
ret

func NOR NOR_a NOR_b
  return = NOR_a !|| NOR_b
ret

func AND AND_a AND_b
  return = AND_a & AND_b
ret

type float
  size = 4
  in = 3
  out = 0
  usage = FPU
;


