use "../../IO/cstd.e"

export int Start_Test(){
	int i
	while (i = 0, i < 100, i++){
		
	}
	if (i == 100){
		i = 10
	}
	if (i == 100){
		i = 100
	}
	else (i == 10){
		i = 100
	}
	return i
}

export int main(){
	return 1
}