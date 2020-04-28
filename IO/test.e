use "cstd.e"
use "boost.e"

func memcpy(int dest, int source, int max_size)(
    cache int i = 0
    while(i < max_size)(
        dest::i = source::i
        i = i + 1
    )
    return 0
)