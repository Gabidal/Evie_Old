use "cstd.e"
use "boost.e"

func banana(int a, int b)(
    int o = 0

    if a > b (
        int x = a + a
        int z = x * x + banana(x, a)
        o = 3 * z + x
    )

    int c = a + b - o
    return c
)