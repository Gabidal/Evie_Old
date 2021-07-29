static std{

	long MAX_CONCOLE_BUFFER_LENGHT = 4096

	func Print(string x){
		internal_print(x.Value(), x.Size()->long)
	}

	string Read(){
		string Result.string()

		Result.Characters.Array = Allocate<char>(MAX_CONCOLE_BUFFER_LENGHT)

		Result.Characters.Size = internal_read(Buffer, MAX_CONCOLE_BUFFER_LENGHT)
		
		Result.Characters.Capacity = MAX_CONCOLE_BUFFER_LENGHT

		result Result
	}

}