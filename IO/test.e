using "cstd.e"

export func _start()(
	return main()
)

export func main()(
	int a = 1
	return get(@a)
)

func get(int i)(
	return i::0
)