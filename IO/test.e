use "cstd.e"
use "boost.e"

type apple(){
	size (
		int a
		int b
		int c
		int ptr d
	)
}

main(){
	apple x
	return @x.d[1]
}