var return = 0
var false = 0
var true = 1

func NAND NAND_a NAND_b 
  if NAND_a == false
    if NAND_b == false
      return = true
    else
      return = true
    end
  else
    if NAND_b == true
      return = false      
    else
      return = true
    end
  end
ret