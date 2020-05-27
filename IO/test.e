use "cstd.e"

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
	int ptr a =	@x.d:10
	return a
}