use "../../STD/STD.e"
#use "https://github.com/Gabidal/Evie/STD/STD.e"

export int main(){
	jump Start_Test
	return 1
}

int foo(int x,int y){
	return 5
}

int foo(float x, float y){
	return 1
}

int bar(int x, int y){
	return 2
}

export int Start_Test(){
	func ptr fuz = foo

	#if (bababui){
	#	fuz = foo
	#}
	#else (express){
	#	fuz = bar
	#}
	#
	#if (alibaba){
	#	return fuz(1, 1)
	#}
	#else (joonas){
	#	return fuz(1, 1)
	#}

	return fuz(1, 1)
}