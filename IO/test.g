using "std.g"

type A
(
	var a = 1
	var b = 2
	var c = 3
)

func main()
(
	new A a
	var b = get(a, 0)
	b = b + get(a, 4)
	return b
)

main()