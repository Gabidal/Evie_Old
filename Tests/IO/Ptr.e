use "../../IO/cstd.e"

export int Start_Test(){
	int val = 10
	int ptr a = val
	int ptr ptr b = a
	return a

	
	int ptr ptr ptr c = b
	int ptr ptr ptr ptr d = c
	int ptr ptr ptr ptr ptr e = d
	int ptr ptr ptr ptr ptr ptr f = e
	return f
}

export int main(){
	Start_Test()
	return 1
}