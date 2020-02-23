type var()(
	Size 4
	Static 0
)

var a = 1
var b = 2
var c = a + b

type byte()(
	Size 1
	Static 0
)

byte d = 1
byte e = 2
byte f = d + e
if (a < b)(
	if (b > c)(
		if (d == e - f)
		(
			return 1
		)
	)
)