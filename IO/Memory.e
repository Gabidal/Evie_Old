char ptr __CAST__

T ptr Allocate<T>(int Size){
	return (internal_allocate((Size * T.size)->long)->__CAST__)->T	
}

T ptr Allocate<T>(long Size){
	return (internal_allocate(Size * (T.size)->long)->__CAST__)->T	
}

T ptr new<T>(T Obj){
	return (internal_allocate(Obj.size)->__CAST__)->T	
}