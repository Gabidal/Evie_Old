type char{
    size = 1
}

type int{
    size = 4
}

type long{
    size = 8
}

type bool{
    size = 1
}

bool Is(){
    return true
}

char ptr Inner(long size){
    return size->(char ptr)
}

# fix where -> T pre Outer<T>(){} the 'pre' is wrong but still somehow used as a inheritance.
T ptr Outer<T>(long Size){

    return Inner(Size * T.size)->(T ptr)

}

type inheritable{
    int x
    int a
    int b

    int ptr Do(){
        return this->(int ptr) + 4->(int ptr)
    }

    inheritable ptr inheritable(){
        return (this + inheritable.size)->(inheritable ptr)
    }
}

type inherit{
    inheritable y
}

export int main(){
    int Num = 123
    long r = Num->long - 48
    int a = 1
    int ptr b = a
    if (b == 2){
        inheritable maybe.inheritable()

        int ptr dont = maybe.Do()

        inherit inh
        r = inh.y.x->long

        int i = 0

        if (Is() == true){
            i = 0
        }

        char ptr c = Outer<char>(r)
        
        while (1 < 2){
            a = a + b[i]
            return a
        }

        return -1
    } 

    return 1 + a 
}

export int Start_Test(){
    return main()
}