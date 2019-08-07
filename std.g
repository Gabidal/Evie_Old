var return = 0
var false = 0
var true = 1

type Math
  var c = 123
  var bits : 123
  func NAND a b 
    return = a !& b
  ret

  func OR a b
    return = a || b
  ret

  func XOR a b
    return = a !| b
  ret

  func NOR a b
    return = a !|| b
  ret

  func AND a b
    return = a & b
  ret
;

type float
  func make %name %val
    var %name = %val
  ret
;
