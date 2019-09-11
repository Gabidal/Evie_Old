var header = 0
var carry = 0
var char.i = 0
str char.s : 20
str reverse.s : 512


func gout(name)
(
  var getLenght = 0
  #get the string length
  getLenght = size(name)
  #call sys print
  sys 4 1 name getLenght 80h carry
)

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
