use "cstd.e"

type Cat{
    int Speed = 12
    int Attack = 23
    int Defence = 34
}

#int Get_Speed(Cat ptr){
    #return 1
#}

int main(){
    Cat ptr c = Cat(allocate(4))
    #c.Get_Speed()
    return 0
}