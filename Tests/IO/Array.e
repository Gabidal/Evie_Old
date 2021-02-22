use "../../IO/cstd.e"

export int Start_Test(){
	int ptr a = allocate(int.size * 10)
	a[1] = 1
	int b = a[1]
	return b
}

export int main(){
	return 1
}