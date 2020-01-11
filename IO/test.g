func banana(a)
(
	a = a + 4
	return a
)

func apple(a)
(
	return 4
)

func main()
(
	var a = 1
	var b = 2
	var c = a + b
	var d = banana(1)
	var e = apple(2)
	if (d == e)
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