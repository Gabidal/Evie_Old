use "cstd.e"

int main() {
	int a = apple(1, 2, 3, 4, 5, 6)
	int b = banana(1, 2, 3, 4, 5, 6, 7) 
	return a + b
}

int banana(int a, int b, int c, int d, int e, int f, int g){
	return a + b + c + d + e + f + g 
}

int apple(int a, int b, int c, int d, int e, int f){
	return a + b + c + d + e + f
}