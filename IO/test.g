use std.g

type vector()
(
  var a = 2
  var b = 1

  func combine(this, other)
  (
    this : a = this : a + other : a
    this : b = this : b + other : b
  )
)

func main()
(
  new static vector a
  new vector b
  a.combine(b)
)