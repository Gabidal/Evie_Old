using "cstd.e"

export func _start()(
	return main()
)

export func main()(
	int a,
	int b,
	int c,
	int d,
	int e,
	while (a < 10)(
		a:b = b:c + c:d - d:e * e:a
	)
)