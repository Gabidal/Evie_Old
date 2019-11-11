type PTR
(
  var N = 0
  func get(this)
  (
    return this
  )
  func add(this, n)
  (
    this : N = n
  )
)

type vector
(
  var Size = 0
  var Start_Pos = 0
  var End_Pos = 0
  func combine(this, other)
  (
    this : Size = this : Size + other : Size
    this : Start_Pos = this
    this : End_Pos = this : Size + 1
  )
  func puch_back(this, n)
  (
    new PTR p
    p.add(n)
  )
)