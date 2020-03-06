type int()(
	Size 4
)

export main()(
	int a = 1
	int b = 2
	int c = square(a, b)
	return c
)

func square(int a, int b)(
	int c = a * b
	return c
)