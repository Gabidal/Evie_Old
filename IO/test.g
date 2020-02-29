type char()(
	Size 1
)

type const()(
	Static 2
)

func main(char b, char c)(
	const char a
	b = b << 2
	a = b * b - c
	return a
)