$use "cstd.e"

func banana(int a, int b, int c, int d, int e, int f, int g) {
    #int result = ((((a * b) + (c * d)) - (e * f)) + g)
    int result = a * b + c * d - e * f + g
    return result
}

main() {
    return banana(1, 2, 3, 4, 5, 6, 7)
}