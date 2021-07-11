#use "../../IO/cstd.e"
use "https://github.com/Gabidal/Evie/IO/cstd.e"

export int main(){
	Start_Test()
	return 1
}

int plain foo(int ,int){
	return 5
}

#void* (*)(int, int) = foo

export int Start_Test(){
	int ptr fuz = foo
	return fuz()
}