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
	var b = & a:0
	return b
)

main()