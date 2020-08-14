use "cstd.e"

type A{
    size 2
}

type bar{
    int m = 0
    int n = 1
}

#inherit foo members into baz
type bar baz{
    int i = 2
    int ptr j = 3
    int k = 4
}

type foo{
    baz x
    baz y
    baz z
}

type test{
    int size
    foo a
    foo b
    foo c
}

#return the address of the &this.a.x.m
ptr test.get(){
    return a.x.m
}

#return the size as an 32bit reg
int test.size(){
    return size
}

int ptr temp(type a, type b){
    return a
}

func banana(){
    func a #(int x) {return 1}
    return a
}

func ptr apple(){
    func ptr a #= new func
    return a
}

func function_pointters(){
    #if the paranthesis arent after the function name the function name return its own address.
    func normal_reference = banana

    #if the new func is a pointter it has the array offsetting ability.
    func ptr function_pointter_as_array_handle = banana

    #the function returning type doesnt matter if the function hasnt been called.

    #these same features can be returned.
    normal_reference = banana()

    function_pointter_as_array_handle = apple()
}

func copy(){
    int a
    int b
    int c = memcpy(a, b, 1.123)
}

func main(int x) {
    test first

    #the post prosessing can put the object fetching the function as first parameter
    int ptr a = first.get(1, 2) + first.size(1 + 2)

    #list
    int ptr list = new(100)

    #if the other side of the operator is also an ptr then use the mem of variable a
    #otherwise load the address of that ptr a points to and do the operator to it
    a = 1 + 2
    int b = -a + 2
    a = x * 2
    b = x * 2 + a

    if (a * 2 == a - 1){
    }
    else {
    }

    #the way to change the pointter value is to manage the offsetter value
    #you dont want to change the initial value of the pointter just add an offsetter when you use it
    if (a[1] == 1){
    }
    else (a[2] == 1){
    }

    #give the content of 'first' to 'second'
    test second = first

    #the copy of the object into heap
    test ptr third #= new(first)
    
    #the reference of the first object
    test ptr fourth = first

    #stack list
    fourth fifth = fourth[123]

    #pointter list
    fourth ptr fifth = fourth[123] 



    return second.get()
}