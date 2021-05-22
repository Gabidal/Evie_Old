char ptr BYTE_POINTER{}

T ptr Allocate<T>(int Size){
	T ptr Return_Cast_Type
	return (internal_allocate((Size * T.size)->long)->BYTE_POINTER)->Return_Cast_Type	
}

T ptr Allocate<T>(long Size){
	T ptr Return_Cast_Type
	return (internal_allocate(Size * (T.size)->long)->BYTE_POINTER)->Return_Cast_Type	
}

func Deallocate<T>(T ptr Address, int Size){
	deallocate(Address->BYTE_POINTER, Size->long)
}

func Deallocate<T>(T ptr Address){
	deallocate(Address->BYTE_POINTER, Address.size->long)
}

func Deallocate<T>(T ptr Address, long Size){
	deallocate(Address->BYTE_POINTER, Size)
}

T ptr New<T>(){
	return (internal_allocate(T.size)->BYTE_POINTER)->T	
}