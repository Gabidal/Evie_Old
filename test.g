use std.g
var x = 1
var y = 1
var z = 0
str banana = "\nbananas\n"
str apple = "\napple\n"

func main
  z = y + x
  y = x - z
  x = z * y
  z = y / x
  gout %banana %banana.size
  banana = apple 
  gout %apple %apple.size
ret 
