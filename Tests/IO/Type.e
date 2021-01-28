use "../../IO/cstd.e"

type Banana{
	int Sugar = 1
	int Protein = 2
}

Banana ptr Banana(Banana ptr this){
	this.Sugar = 3
	this.Protein = 4
	return this
}

export int Start_Test(){
	Banana x.Banana()
	return x.Sugar
}

export int main(){
	return 1
}