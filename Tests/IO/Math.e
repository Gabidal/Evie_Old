use "../../IO/cstd.e"

export int Start_Test(){
	int a = 1 + 2
	int b = a + 3
	int c = b * a
	int d = c / b
	return d + a + b - c
}

export int main(){
	return 1
}