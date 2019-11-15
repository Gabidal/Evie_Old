type banana
(
  var a = 2
  func v(this, c)
  (
    return c + a
  )
)

func main()
(
  new banana b
  var d = 3
  b.v(b.a + d)
)

main()