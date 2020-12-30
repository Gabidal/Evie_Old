use "cstd.e"

type banana{
	int x = 1
	int y = 2
	int z = 3
}

banana ptr export main(){
	banana b
	banana c
	c = b
	return c
}