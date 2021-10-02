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

			memcpy<T>(tmp, Array, Size)

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

	int List<T>.Size(){
		return Size
	}

	func List<T>.Resize<T>(int New_Size){
		if (Size >= New_Size){
			return
		}

		T ptr tmp = Allocate<T>(New_Size)

		memcpy<T>(tmp, Array, Size)

		Array = tmp

		Capacity = New_Size
		Size = New_Size
	}

	List<T> ptr List<T>.Reverse<T>(){
		List<T> ptr Result = New<List<T>>.List<T>()
		Result.Resize(this.Size())
		
		while (int i = 0; i < this.Size(); i++){
			Result.Set(i, this.At(this.Size() -1 - i))
		}

		return Result
	}

	func List<T>.Set<T>(int i, T data){
		this.Array[i] = data
	}

	T ptr List<T>.Last<T>(){
		return this.Array + this.Size()
	}

	T ptr List<T>.First<T>(){
		return this.Array
	}

	func List<T>.Clean(){
		this.Size = 0
		this.Capacity = 0
	}
	
	#This append adds to the left side list and then returns it
	#Warning: this function modifies content of 'x'
	func List<T>.Append<T>(List<T> ptr x, List<T> y){
		x.Resize(y.Size())

		Memcpy<T>(x.Last(), y.First(), y.Size())
	}

	#This append returns a new combined list
	T ptr List<T>.Append<T>(List<T> x, List<T> y){
		List<T> Result.List<T>()
		Result.Resize(x.Size() + y.Size())

		Memcpy<T>(Result.First(), x.First(), x.Size())
		
		Memcpy<T>((Result.First() + x.Size() - 1)->address, y.First(), y.Size())

		return Result
	}

	#Finds the index of element and then returns the index
	int List<T>.Find<T>(T ptr Target){
		while (int i = 0; i < this.Size(); i++){
			if (T.size <= BITS_MODE){
				if (Target == this.At(i)){
					return i
				}
			}
			else{
				if (Compare(Target, this.At(i))){
					return i
				}
			}
		}
		return -1
	}
}