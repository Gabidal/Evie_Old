use std.g

type vector()
(
  var a = 2
  var b = 1

  func combine(this, other)
  (
    -> a = -> a + other : 0
    -> b = -> b + other : 1
  )
)

func main()
(
  new vector a
  new vector b
)