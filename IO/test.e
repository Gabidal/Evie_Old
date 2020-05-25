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
		banana c
	)
}

main(){
	apple x;
	char ptr a = @x.c.a
	return
}