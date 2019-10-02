
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
  new vector banana
  new vector apple
  apple.a = banana.a + apple.b
  if apple.a == banana.a
  (

  )
  else
  (

  )
)
