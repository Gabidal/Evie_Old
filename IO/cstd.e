use "sys.e"


type cpp int{
	size = 4
}

type cpp short{
	size = 2
}

type cpp char{
	size = 1
}

type cpp float{
	size = 4
	format = decimal
}

type cpp double{
	size = 8
	format = decimal
}

type cpp long{
	size = 8
}

type string{
	size = 1
}

import type ptr cpp allocate(int size)
#import func cpp deallocate(type ptr, int)

func memcpy(type ptr dest, type ptr source, int Size){
    while (int i = 0, i < Size, i++){
        dest[i] = source[i];
    }
    return;
}