char ptr __CAST__{}

T ptr Allocate<T>(int Size){
	T ptr Return_Cast_Type
	return (internal_allocate((Size * T.size)->long)->__CAST__)->Return_Cast_Type	
}

T ptr Allocate<T>(long Size){
	T ptr Return_Cast_Type
	return (internal_allocate(Size * (T.size)->long)->__CAST__)->Return_Cast_Type	
}

T ptr new<T>(T Obj){
	return (internal_allocate(Obj.size)->__CAST__)->T	
}