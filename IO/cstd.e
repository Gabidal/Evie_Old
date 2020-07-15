use "sys.e"

type int{
	size 4
}

type short{
	size 2
}

type char{
	size 1
}

type float{
	size 4
	state decimal
}

type double{
	size 8
	state decimal
}

type long{
	size 8
}

type string{
	size 1
}

export func main

func memcpy(int ptr dest, int ptr source, int Size){
    int i = 0;
    while (i < Size){
        dest[i] = source[i];
        i = i + 1;
    }
    return;
}