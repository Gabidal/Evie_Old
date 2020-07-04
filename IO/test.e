$use "cstd.e"

type foo(){
    int m
    int n
}

#inherit foo members into baz
foo baz(){
    int i
    int ptr j
    int k
}

type foo(){
    baz x
    baz y
    baz z
}

type test(){
    int size
    foo a
    foo b
    foo c
    func get
}

#all the member functions need to be copyed into the newly made object
test.get(test ptr this){
    return @this.a.x.m
}

test.size(test ptr this){
    return this.size
}

$replace(test ptr this, operator =, test ptr other){
    memcpy(this[0], other[0], this.size())
}

func main() {
    test first
    int ptr a = first.get(@first)
    #if the other side of the operator is also an ptr then use the mem of variable a
    #otherwise load the address of that ptr a points to and do the operator to it
    a = 2 + 1
    if (a == 2){
        return first.get(@first)
    }
    #the replace will replace this by memcpy()
    test second = first
    return second.get(@second)
}