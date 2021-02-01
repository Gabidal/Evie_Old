use "../../IO/cstd.e"

type Fruit{
	int Type = 0
}

Fruit Banana{
	int Sugar = 1
	int Protein = 2
	int size = 6
}

Banana ptr Banana(Banana ptr this){
	this.Sugar = 3
	this.Protein = 4
	this.size = 7
	this.Type = 1
	return this
}

export int Start_Test(){
	Banana x.Banana()
	return x.Sugar
}

export int main(){
	return 1
}