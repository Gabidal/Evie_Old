use "sys.e"

type int()(
	size 4
)

type short()(
	size 2
)

type char()(
	size 1
)

type float()(
	size 4
)

type double()(
	size 8
)

type long()(
	size 8
)


type void(){
	state func
}

export func main

void memcpy(int dest, int source, int Size){
    cache int i = 0;
    while (i < Size){
        dest[i] = source[i];
        i = i + 1;
    }
    return;
}