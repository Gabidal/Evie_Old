var a = 1
var b = 2
var c = 3

func sum a b
  a = a + b
  return a
ret

func negate a
  a = a - a
  return a
ret

func main
 a = negate a + sum a b
ret
