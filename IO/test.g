using "std.g"

func main()
(
	std_init()
	var a = 1
	var b = 2
	a : 30 = move(&a, &b : 30, 70)
	return a
)

main()