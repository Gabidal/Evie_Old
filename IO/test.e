type int {
    size = 4
}

type char{
    size = 1
}

int a = 1

export int Start_Test(){
    jump main
    return 0
}

export int main(){
    return a
}
