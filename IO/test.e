use "cstd.e"

type cpp Cat{
    int Speed = 12
    int Attack = 23
    int Defence = 34
}

#int Get_Speed(Cat ptr){
    #return 1
#}

int cpp export main(){
    Cat ptr c = Cat(allocate(4))
    #c.Get_Speed()
    return 0
}