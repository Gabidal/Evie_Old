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

type long()(
	size 8
)

type float()(
	size 8
)

type double()(
	size 12
)

export func main,

func memcpy(int dest, int source, int Size){
    cache int i = 0;
    while (i < Size){
        dest[i] = source[i];
        i = i + 1;
    }
    return;
}