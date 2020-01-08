func banana(x, y)
(
	var z = x + y
	return z
)

func main()
(
	var a = 1
	var b = 2
	if (a < b)
	(
		a = banana(a, b)
	)
	return a
)