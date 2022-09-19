type int{
    size = 4
}

type long{
    size = 8
}

export int main(){
    int a = 1
    int ptr b = a 
    if (b == 2){
        return -1
    } 
    return 1 + a 
}

export int Start_Test(){
    return main()
}