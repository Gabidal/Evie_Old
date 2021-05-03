use "../../IO/cstd.e"

export int Start_Test(){
	char ptr Cast
	int ptr a = internal_allocate((int.size * 10)->long)->Cast
	int ptr ptr b = a
	b[0, 1] = 1
	int c = b[0, 1]
	return c
}

export int main(){
	return 1
}