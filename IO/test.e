use "cstd.e"
#use "https://github.com/Gabidal/Evie/IO/cstd.e"


func main(int x) {
}


func Algebra(int uknown){
    #constant optimisation
    int a = 123
    int b = 456
    int c = a + b

    #useless value deletion
    int d = a + c
    d = d - c

    #useless variable deletion
    int e = a * 2 == a - 1
}


func Normal_F(){
}

func ptr UnCommon_F(){
    return Normal_F
}

func Function_pointters(){
    func ptr FPtr = Normal_F
    FPtr = UnCommon_F()
}


func Pointters(int x){
    int a = x

    #make a pointing address
    int ptr b = a

    #make a pointing address from a pointing address
    int ptr ptr c = b

    #load from pointing address
    int ptr d = c

    #load from pointing address and load from it
    a = c
}

func Array(){
    int a = 0 #int(100)
    int ptr b = a

    a[2][5] = 123
    b[1][4] = 456
}

#inheritance testing
type foo {
    int width
}

foo bar {
    int height
}

bar baz {
    int depth
}

func Members(){
    baz a
    a.width = a.height * a.depth
}

func Condions(int x, int y, int z){
    if (x - 2 == y * 2){
        if (x +1 == z*4){
        }
    }
    else (y -2 == z * 3){
        if (y-3 == x*4){
        }
    }
    else {
        if (x + 5 == x - 4){
        }
    }
}

func Loops(){
    int b
    while (int i = 0; i < 10; i++){
        int a = 123
        b = a + + i
    }
    int c = b * b
}