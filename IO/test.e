type int()(
    size 4
)

type baz(){
    size (
        int i
        int ptr j
        int k
    )
}

type foo(){
    size (
        baz x
        baz y
        baz z
    )
}

type test(){
    size (
        foo a
        foo b
        foo c
    )
}

func main() {
    test ptr me
    int ptr a = @me.b.y.j
    a[1] = 2
    return 0
}
