use "../../IO/cstd.e"

export int main(){
	Start_Test()
	return 1
}

int foo(){
	return 5
}

export int Start_Test(){
	int ptr fuz = foo
	return fuz()
}