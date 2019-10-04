
type vector()
(
  var b = 1
  var a = 2

  func init(this, aa, bb)
  (
    -> a = aa
    -> b = bb
  )
)

func main()
(
  var a = 1
  var b = 2
  new vector banana
  new vector apple
  banana.init(a, b)
  apple.init(a, b)
)
