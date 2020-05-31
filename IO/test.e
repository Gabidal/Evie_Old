use "cstd.e"
use "boost.e"
use "glfw3.lib"

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
	char b = 0
	banana(b, 1)
	return a
}

func banana(int a, int y){
	return 0;
}