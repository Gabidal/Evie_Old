func banana(a)
(
	if (a == 10)
	(
		return 4
	)
	else
	(
		return 3
	)
)

func apple(a)
(
	return 4
)

func main(a)
(
	var b = 2
	var c = a + b
	var d = banana(10)
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