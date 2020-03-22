using "cstd.e"

cover f(static int x)(
	x*x
)

export func main()(

	int a = f(banana())

	non-static(
		int a = banana()*banana()
	)

	static(
	int r = banana()
	int a = r*r
	)


	return a
)