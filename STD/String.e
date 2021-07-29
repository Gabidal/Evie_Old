static std{
	type string{
		List<char> ptr Characters.List<char>()
	}

	int string.Size(){
		return this.Characters.Size
	}

	char string.At(int i){
		return this.Characters.At(i)
	}

	char ptr string.Value(){
		return this.Characters.Array
	}

	string To_String(int x){
		string Result.string()

		while (1 < 2){
			int Remainder = x % 10
			x = x / 10

			char Digit = Remainder + 48

			Result.Characters.Push_Back(Digit)

			if (x == 0){
				return Result
			}
		}
	}

	int To_Int(string x){
		int Result = 0;
		while (int i = x.Size() -1; i >= 0; i--){
			char Character = x.At(i) - 48

			Result = Result * 10 + Character
		}

		return Result
	}
}