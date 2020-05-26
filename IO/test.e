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
	int ptr a = x.c[0]
	return
}