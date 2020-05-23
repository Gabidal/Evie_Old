use "cstd.e"
use "boost.e"

type apple(){
	size (
		int a
		int b
		int c
	)
}

main()(
	apple x;
	int a = @x
	a::0 = 12
	a::4 = 3
	a::8 = 5
	x:0 = 0
	int b = 1
	return
)