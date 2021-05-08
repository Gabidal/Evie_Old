type List<T>{
	int Capacity = 1
	int Size = 0
	T ptr Array = Allocate<T>(Capacity)
}

func List<T>.Add<T>(T Element){
	if (Size >= Capacity){
		#allocate new heap space
        Capacity = Size * 2
        T ptr tmp = Allocate<T>(Capacity)

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