
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
  var a = 0
  var b = 10
  while (a : b)
  (
    new vector banana
    #this makes pointer variable named banana that points to the new class vector.
  )
)
