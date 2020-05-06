use "cstd.e"
use "boost.e"

func memcpy(int dest, int source, int Size)(
    int i = 0
    while (i < Size)(
        dest::i = source::i
        i = i + 1
    )
    return 0
)