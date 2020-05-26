use "cstd.e"

type banana(){
	size (
		int a
		int b
		int c
	)
}

type apple(){
	size (
		int a
		int b
		int ptr c
	)
}

main(){
	apple x;
	int ptr a = @x.c[0]
	return a
}