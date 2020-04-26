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
    ptr:0 = 1
    ptr:1 = 2
    ptr:3 = 3
    return ptr
)