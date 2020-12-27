use "cstd.e"

type banana{
	int x = 1
	int y = 2
	int z = 3
}

banana ptr set(banana ptr this, banana ptr that){
	this.x = that.x
	this.y = that.y
	this.z = that.z
	return this
}

banana ptr export main(){
	banana b
	banana(b)
	banana c
	c.set(b)
	return b
}