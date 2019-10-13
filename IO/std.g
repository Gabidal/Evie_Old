var header = 0
var carry = 0

func gin(name)
(
  var getLenght = 0
  getLenght = size(name)
  sys 3 2 name getLenght 80h carry
)

func exit()
(
  sys 1 0 0 0 80h carry
)
