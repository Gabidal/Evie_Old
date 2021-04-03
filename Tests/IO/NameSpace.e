use "../../IO/cstd.e"

#cumulatie type or perhaps cum type? this joke was brought to you by lehtojo 25/3/2021/13:18.
#Go and vote for the keyword to be used for using/inlining namespaces :D
#https://docs.google.com/forms/d/e/1FAIpQLSfR5CAMP7dXWwrp_lcAa4PrpHgiuRlQxReuvX2oMiFtULR6vQ/viewform?usp=sf_link

#a namespace is like a type class but everything inside it is static.
type Banana{	#In the declaration of Banana we can set it to static
				#that way everything inside it will be static.
	
	#Or we can let Banana type be as it is, and set the static prefix to every child inside Banana.
	int X = 1
	static int Y = 2
	int Set(int x){
		X = x
		return X + 1
	}
}

int Banana.Get(){
	return Y
}

static Apple{
	#Both of these member varibles are now static because the parent class is a static type.
	int X = 2
	int Y = 3
}

export int Start_Test(){
	Banana b
	int B_X = b.Get()
	return Banana.Y + Apple.Y
}

export int main(){
	return 1
}