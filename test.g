
type vector()
(
  var b = 1
  var a = 2

  func c(this)
  (
    -> a = -> a + -> a
    -> b = -> b * -> a
    return -> a
  )
)

func main()
(
  var a = 123
  new vector banana
  banana.a = banana.a + banana.b
)
