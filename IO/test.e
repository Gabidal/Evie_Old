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
    test me 
    me.c.x = 2
    return 0
}