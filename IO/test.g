func banana(a)
(
  a = a + a
  return a
)


func main()
(
  var a = 2
  var b = 3
  b = a + banana(a + a) * b
)