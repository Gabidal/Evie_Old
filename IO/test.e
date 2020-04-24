use "cstd.e"
use "boost.e"

func a(int x)(
    return (x::0 + x() + 1)
)

func b(int x)(
    return (x:0 + x() + 1)
)

func c(int x)(
    return (@x + x() + 1)
)