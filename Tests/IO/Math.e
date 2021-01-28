use "../../IO/cstd.e"

int sum(int a){
	return 3 + a
}

export int Start_Test(){
	int a = 1 + 2
	int b = sum(a)
	int c = b * a
	int d = c / b
	return d + a + b - c
}

export int main(){
	return 1
}