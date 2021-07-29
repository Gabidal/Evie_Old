use "../../STD/STD.e"

use std

export int Start_Test(){
	List<int> a.List<int>()
	a.Add(5)
	a.Add(2)
	a.Pop_Back()
	return a.At(0)
}

export int main(){
	#jump Start_Test
	return 1
}