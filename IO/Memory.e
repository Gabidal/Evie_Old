T ptr Allocate<T>(int Size){
	return internal_allocate(Size->long)->T	
}

T ptr Allocate<T>(long Size){
	return internal_allocate(Size)->T	
}

T ptr new<T>(T Obj){
	return internal_allocate(Obj.size)->T	
}