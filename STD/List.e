static std{
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

	T List<T>.At<T>(int i){
		if (i > Size){
			return 0->T
		}
		return Array[i]
	}

	func List<T>.Reverse<T>(){
		while (int i = 0; i < this.Size; i++){
			T Tmp = this.Array[this.Size - 1 - i]

			this.Array[this.Size - 1 - i] = this.Array[i]

			this.Array[i] = Tmp
		}
	}
}