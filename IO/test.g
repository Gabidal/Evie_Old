using "std.g"

func main()
(
	var a = 1
	var b = 4
	move(&a, &b, 1)
	while(a != b)
	(
		if (a < b)
		(
			a = a + 1
		)
		else
		(
			b = b + 1
		)
		if (a > b)
		(
			a = a - 1
		)
		else
		(
			b = b - 1
		)
	)
	return a
)

main()