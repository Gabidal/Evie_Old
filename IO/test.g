using "cstd.e"

export main(int a, int b)(
    int r = square(a, b)
    return r
)

func square(int a, int b)(
    int c = a * b
    return c
)