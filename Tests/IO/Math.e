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

	return Test_Fpu(1.2, 2.3)->int

	return -6
}

float Test_Fpu(float a, float b){
	return 1.2 + b - a - 1.3
}

export int main(){
	int a = 1
	return a
}