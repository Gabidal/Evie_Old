type List<T>{
	int Capacity = 1
	int Size = 0
	T ptr Array = allocate(T.size * Capacity)
}


func List<T>.Add<T>(T Element){
	if (T.size + Size > Capacity){
		#allocate new heap space
        Capacity = Size * 2
        T ptr tmp = allocate(Capacity * T.size)

        memcpy<int>(tmp, Array, Size * T.size)
        Array = tmp
	}
	Array[Size] = Element
	Size = Size + 1
}