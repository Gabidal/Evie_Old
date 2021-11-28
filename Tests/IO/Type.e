use "https://github.com/Gabidal/std/blob/main/std.e"

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

int Get_Sugar(Banana ptr b){
	return b.Sugar
}

int is_Banana(Fruit ptr f){
	return Get_Sugar(f)
}

export int Start_Test(){
	Banana x.Banana()
	return is_Banana(x)
}

export int main(){
	Start_Test()
	return 1
}
