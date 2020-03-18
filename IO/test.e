using "cstd.e"

export func _start()(
	return main()
)

export func main()(
	int a = 0
	int b = 0
	int c = 0
	int d = 0
	while (a < 10)(
		a:b = b:c + c:d - d:a
	)
)