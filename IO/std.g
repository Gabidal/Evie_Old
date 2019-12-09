var true
var false
var null
var size_v
var size_f
var size_d
var size_c

#inizaliation of std variables.
func std_init()
(
	true = 1
	false = 0
	null = 0
	size_v = 4
	size_f = 4
	size_d = 8
	size_c = 1
)

#num to char.
func ntc(c)
(
	c = c + 48
	return c
)

#char to num.
func ctn(i)
(
	i = i - 48
	return i
)

func move(&x, &y, s)
(
	while (s > 0)
	(
		x : s = y : s
		s = s + 1
	)
)

func sum(&x, &y)
(
	var i = 0
	while(x : i != 0 y : i != 0)
	(
		x : i = y : i + x : i
		i = i + 1
	)
)
