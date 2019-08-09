use std.g

func getFromNAND y x
  var a = 0
  var z = 0
  z = y * 128
  z = z + x
  a = NAND2D : z
  return = a
ret

func NAND a b 
  return = a !& b 
ret 

func main
  new NAND1D NAND2D : 128
  getFromNAND 0 0
  getFromNAND 0 1
  getFromNAND 1 0
ret 
