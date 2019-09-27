use util.g

func apple(b)
(
  return b
)

func banana(a)
(
  return a
)

type vector(a)
(
  var b = 1
  var c : 2
  if a == b
  (
    c : 0 = &apple()
  )
  else
  (
    c : 0 = &banana()
  )
)

func main()
(
  var a = 1
  new vector(a) foo
)
