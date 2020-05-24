use "cstd.e"
use "boost.e"

type apple(){
	size (
		int a
		int b
		int c
	)
}

main(){
	apple x;
	char ptr a = @x.c
	a[1] = 1
	return
}