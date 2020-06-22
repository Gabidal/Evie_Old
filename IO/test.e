$use "cstd.e"
$use "boost.e"

func f(int a, int b, int i, int j) {
    int result = a * b + i * j
    return result
}

main() {
    return f(1, 2, 3, 4)
}