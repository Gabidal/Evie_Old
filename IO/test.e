use "cstd.e"

int main(){
    char ptr b = "Hello World!"
    internal_print(b, Size_Of(b))
    return 0
}

int Size_Of(char ptr s){
    int result = 0
    while (s[result] != 0){
        result++
    }
    return result
}