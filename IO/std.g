var true
var false
var null
var size_v
var size_f
var size_d
var size_c

func std_init()
(
	true = 1
	false = 0
	null = 0
	size_v = 4
	size_f = 4
	size_d = 8
	size_c = 1
)

func ntc(c)
(
	c = c + 48
	return c
)

func ctn(i)
(
	i = i - 48
	return i
)

func move(&x, &y, s)
(
	while (s)
		x:0 = y:0
)

type Array
(
	var Size
	var Address
	var Child_Size
)

func Array(this, size, child_size)
(
	this = malloc(size)
	this:0 = size
	this:8 = child_size
	var combined_size = size * child_size
	this:4 = malloc(combined_size)
	return this
)