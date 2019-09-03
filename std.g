var header = 0
var carry = 0

func gout(name)
(
  var getLenght = 0
  getLenght = size(name)
  sys 4 1 name getLenght 80h carry
)

func gin(name)
(
  var getLenght = 0
  getLenght = size(name)
  sys 3 2 name getLenght 80h carry
)

func file.open(name)
(
  sys 5 name 0 0777 80h header
)

func file.make(name)
(
  sys 8 name 0777 0 80h header
)

func file.close()
(
  sys 6 header 0 0 80h header
)

func file.write(text, size)
(
  sys 4 1 text size 80h carry
)

func file.read(name, size)
(
  sys 3 header name size 80h carry
)

