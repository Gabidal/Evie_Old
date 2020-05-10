use "cstd.e"
use "boost.e"

void memcpy(int dest, int source, int Size){
    cache int i = 0;
    while (i < Size){
        dest[i] = source[i];
        i = i + 1;
    }
    if (i < 0){
        return 0;
    }
    return i;
}