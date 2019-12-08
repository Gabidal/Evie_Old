using "std.g"

func main()
(
	std_init()
	var a = 1
	var b = 2
	move(&a, &b, 10)
	return a
)

main()