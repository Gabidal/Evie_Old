type List<T>{
	int Capacity = 1
	int Size = 0
	T ptr Array = (internal_allocate((T.size * Capacity)->long)->char)->T
}

func List<T>.Add<T>(T Element){
	if (Size >= Capacity){
		#allocate new heap space
        Capacity = Size * 2
        T ptr tmp = (internal_allocate((Capacity * T.size)->long)->char)->T

        memcpy<int>(tmp, Array, Size * T.size)

		#deallocate(Array)

        Array = tmp
	}
	Array[Size] = Element
	Size++
}

func List<T>.Pop_Back(){
	Size--
}