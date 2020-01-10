func banana()
(
	return 4
)

func apple()
(
	return 4
)

func main()
(
	var a = 1
	var b = 2
	var c = a + b
	var d = banana()
	var e = apple()
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