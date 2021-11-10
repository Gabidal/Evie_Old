use "https://github.com/Gabidal/std/std.e"

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

func test_all_format_casts(){
	int i = 1

	float a = i->float
	double b = i->double

	i = a->int
	i = b->int

	a = b->float
	b = a->double
}

export int Start_Test(){
	test_all_format_casts()
	Mid m.Mid()
	return m.feature->int
}

export int main(){
	#Start_Test()
	return 1
}