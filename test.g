#std library functions.
use std.g

#make a string.
str abc = "moikkamoi!"

var a = 2
var b = 2
var c = 0

#make main.
func main()
(
  #print string abc.
  gout(abc)
  a = a * a
  b = b * b
  c = a + b
  if a == b
  (
    c = c + b
  )
  else
  (
    c = c + a
  )
)
