use std.g

dynamic type vector
(
  vector(
    a = 0
    b = 1
  )
  var a = 2
  var b = 1

  func combine(this, other)
  (
    this : a = this : a + other : a
    this : b = this : b + other : b
    return a
  )
)

dynamic type string
(
  string(
    a = 0
    b = 1
    c = 2
  )
  var a = 1
  var b = 2
  var c = 3

  func do(this, something, somethingelse)
  (
    this : d = something
    return a + d
  )
)

func banana(this, uncleBeens)
(
  banana(
    this : mask = uncleBeens : mask
    uncleBeens : mask = this : mask
  )
  this : a = uncleBeens : b * uncleBeens : c
)

func main()
(
  new string b
  new vector a.banana(this, b)
  a.combine(b)
)