using "std.g"

func banana(a)
(
	return a
)

func main()
(
	var a = 1
	var b = banana(a) + banana(a)
	move(a:0, b:0, 1)
	return a
)