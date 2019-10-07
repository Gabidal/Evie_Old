type vector()
(
  var b = 1
  var a = 2

  func init(this, aa, bb)
  (
    -> a = aa
    -> b = bb : -> a
  )
)

func main()
(
  var a = 1
  var b = 2
  var c : 10
  new vector apple
  apple.init(a, c)
)
