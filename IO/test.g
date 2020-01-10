func banana()
(
	var a = 4
	return a
)

func main()
(
	var a = 1
	var b = 2
	var c = a + b
	var d = banana()
	if (d == 4)
	(
		return d
	)
	if (a == b)
	(
		return a
	)
	else if	(a < b)
	(
		return b
	)
	else
	(
		return c
	)
)