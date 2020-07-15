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

func memcpy(type ptr dest, type ptr source, int Size){
    if (int i = 0, i < Size, i++){
        dest[i] = source[i];
    }
    return;
}