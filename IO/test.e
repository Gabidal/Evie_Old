use "cstd.e"
use "boost.e"

func square(int num)(
	return (num * num)
)

main()(
	int a = 1
	int b = 2
	return (a + square(b))
)