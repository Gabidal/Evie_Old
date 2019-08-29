var a = 1
var b = 2
var c = 3

func sum x y
(
  var z = 0
  z = x + y
  if x < y
  (
    return x
  )
  else
  (
    return z
  )
)

func main
(
  a = sum a b
)
