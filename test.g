
func apple(b)
(
  return b
)

func banana(a)
(
  return a
)

type vector()
(
  var b = 1
  var a = 2
  func c(d)
  (
    -> b = d * -> a
    d = -> b + -> b
    return d
  )
)

func main()
(
  var a = 1
  new static vector foo
  foo.c()
)
