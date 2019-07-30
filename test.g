var a = 23
var b = 25
var c = 1

func test
  if a != b
    a = b
  else
    if c < a
      c = a
    else
      if c < a
        if c < a
          c = a
        else
          c = b
        end
      else
        c = b
      end
    end
    if c != a
      c = c
    else 
      c = c + c
    end
  end
ret

func main
  test
ret

