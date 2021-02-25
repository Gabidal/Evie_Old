use "../../IO/cstd.e"

type cpp ptr Static_Cast {}

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
	
	int ptr Normal_Cast_needing_Var = 123->Static_Cast
	return Normal_Cast_needing_Var

	int ptr ptr Dynamic_needing_Var = 1234->address
	return Dynamic_needing_Var
}

export int main(){
	Start_Test()
	return 1
}
