type int(){
    size 4
}

type banana(){
    size (
        int a
        int b
        int c
    )
}

func main() {
    banana ptr b
    b.c = 2
    return 0
}