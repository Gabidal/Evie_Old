use "cstd.e"

type banana{
	int x = 1
	int y = 2
	int z = 3
}

banana ptr export main(){
	banana b = banana(allocate(b.size))
	if (b.x == 1){
		b.y = b.x
	}
	else (b.x == b.y){
		b.y = b.z
	}
	else (b.y == b.z){
		b.z = b.x
	}
	banana c
	c = b
	return c
}