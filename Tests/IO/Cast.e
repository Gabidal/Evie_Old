use "../../IO/cstd.e"

type Base{
	int Type = 0
}

Base Mid{
	Type = 1
	float feature = 2.123845
}

Mid Top{
	Type = 2
	int feature = 2
}

export int Start_Test(){
	Mid m.Mid()
	return m.feature->int
}

export int main(){
	Start_Test()
	return 1
}