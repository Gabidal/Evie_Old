use "../../IO/cstd.e"

type Fruit{
	int Type = 3
}

Fruit ptr Fruit(Fruit ptr this){
	this.Type = 4
}

Fruit Banana{
	int Sugar = 1
	int Protein = 2
	int size = 6
	Type = 5
}

int is_Banana(Fruit ptr f){
	return f->Banana.Sugar
}

export int Start_Test(){
	Banana x.Banana()
	return is_Banana(x)
}

export int main(){
	return 1
}