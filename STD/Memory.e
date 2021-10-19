T ptr Allocate<T>(int Size){
	return (internal_allocate((Size * T.size)->long)->(char ptr))->(T ptr)
}

T ptr Allocate<T>(long Size){
	return (internal_allocate(Size * (T.size)->long)->(char ptr))->(T ptr)
}

func Deallocate<T>(T ptr Address, int Size){
	internal_deallocate(Address->(char ptr), Size->long)
}

func Deallocate<T>(T ptr Address){
	internal_deallocate(Address->(char ptr), Address.size->long)
}

func Deallocate<T>(T ptr Address, long Size){
	internal_deallocate(Address->(char ptr), Size)
}

T ptr New<T>(){
	return (internal_allocate(T.size)->(char ptr))->T	
}

func Memcpy<T>(T ptr dest, T ptr source, int Size){
    while (int i = 0, i < Size, i++){
        dest[i] = source[i]
    }
    return
}