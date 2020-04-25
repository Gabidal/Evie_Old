use "cstd.e"
use "boost.e"

func good(int x)(
    return @x
)

func same(int x)(
    cache int y = @x 
    return y
)

func bad(int x)(
    int y = @x
    return y
)