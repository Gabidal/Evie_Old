use "cstd.e"
use "boost.e"

func banana()(
    return 0
)

func apple()(
    return 0
)

func orange()(
    return 0
)

loyal func pear()(
    return 0
)

func main()(
    cache int a = @banana,
    cache int b = @apple,
    int c = @orange,
    int d = @pear,
    while (1 < 2)(
        a()
        b()
        c()
        d()
    )
    return 0
)