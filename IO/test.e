use "cstd.e"
use "boost.e"

type dot()(
    size (
        int x,
        int y,
        int z,
    )
)

func main()(
    dot a
    cache int ptr = @a
    int banana = 0
    ptr::banana = 1
    ptr::0 = 2
    ptr::3 = 3
    return ptr
)