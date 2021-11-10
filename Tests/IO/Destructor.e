use "https://github.com/Gabidal/std/std.e"

export int main(){
	Start_Test()
	return 1
}

type foo{
	int X = 1
	int Y = 2
}

export int Start_Test(){
	foo F = foo(New<foo>())
	foo ptr handle_1 = F

	int x = handle_1.X
	return x
}