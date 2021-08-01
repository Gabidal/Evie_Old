#use "../../STD/STD.e"
use "https://github.com/Gabidal/Evie/STD/STD.e"

export int main(){
	Start_Test()
	return 1
}

int foo(int ,int){
	return 5
}

int foo(float, float){
	
}

int bar(int, int){
	
}

export int Start_Test(){
	func ptr fuz

	if (bababui){
		fuz = foo
	}
	else (express){
		fuz = bar
	}

	if (alibaba){
		return fuz(1, 1)
	}
	else (joonas){
		return fuz(1, 1)
	}

	return fuz()
}