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

func pear()(
    return 0
)

func main()(
    int a = @banana,
    int b = @apple,
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