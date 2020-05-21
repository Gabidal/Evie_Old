use "cstd.e"
use "boost.e"
use "Apple.so"

type apple(){
	size (
		int a
		int b
		int c
	)
}

main()(
	apple x;
	int a = 0
	int b = 1
	memcpy(@a, @b, 1)
	return
)