var a = 23
var b = 25
var c = 1

func testFalse
ret

func testTrue
  a = a + c
  if a < b
    testFalse
  else
    testTrue
  end
ret


func main
  testTrue
  testFalse
ret

