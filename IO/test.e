type int()(
    size 4
)

type baz(){
    size (
        int i
        int j
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
    test me
    me.b.z.i = 2
    return 0
}
