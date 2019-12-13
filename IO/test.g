using "std.g"

func main()
(
	var a = 1
	var b = 4
	while(a != b)
	(
		if (a < b)
		(
			a = a + 1
		)
		if (a > b)
		(
			a = a - 1
		)
	)
	return a
)

main()