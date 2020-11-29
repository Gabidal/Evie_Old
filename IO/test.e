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
    return b + a
}

int main(){
    int a = linkage_1(1)
    return a
}