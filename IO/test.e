$use "cstd.e"
$use "boost.e"

func banana(int a, int b, int c, int d, int e, int f) {
    int result = a * b + c * d - e * f
    return result
}

main() {
    return banana(1, 2, 3, 4, 5, 6)
}