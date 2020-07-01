type int()(
    size 4
)

type foo(){
    size (
        int x
        int y
        int z
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
    me.b.y = 2
    return 0
}