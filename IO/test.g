func main()
(
  var a = 2
  var b = 3
  if (a - b < 0)
  (
    a = a - 1
  )
  else if (a == b)
  (
    b = b - 1
  )
  else
  (
    a = b
  )
  if (a == b)
  (
    a = b + a
  )
)