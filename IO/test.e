use "cstd.e"

type apple{
	int x = 1
	int y = 2
	int z = 3
}

type banana{
	int x = 1
	int y = 2
	apple a
	apple(a)
}

banana ptr export main(){
	banana b = banana(allocate(b.size))
	b.banana().banana().x = b.banana().banana().y

	if (b.x == 1){
		b.y = b.x
	}
	else (b.x == b.y){
		b.y = b.a.y
	}
	else (b.a.x == b.a.y){
		b.a.x = b.x
	}
	banana c
	c = b
	return c
}