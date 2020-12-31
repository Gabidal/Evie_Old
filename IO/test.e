use "cstd.e"

type banana{
	int x = 1
	int y = 2
	int z = 3
}

int export apple(banana ptr this){
	return this.banana().banana().z
}