type int{
    size = 4
}

int linkage_1(int b) {
    int a = b
    b = 1 + a
    return a + b
}

int linkage_2(int b) {
    int a = b
    a = 1
    return 2 * b + 2 * a
}