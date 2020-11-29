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

int linkage_3(int b) {
    int a = b    
    int i = 0

    int c = b
    int d = c
    int e = a

    int j = i

    while (i < 3) {
        a = i
        b = i + 1
        i++
    }

    return a + b
}

int main(){
    int a = linkage_1(1)
    return a
}