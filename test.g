var a = 23
var b = 25
var c = 0

func banana
  a = a * a
  b = b * b
ret

func apple
  a = b
  b = a
  c = a + b
ret

func main
  banana
  apple
ret

