use "sys.e"

type int()(
	Size 4
)

type short()(
	Size 2
)

type char()(
	Size 1
)

type long()(
	Size 8
)

type float()(
	Size 12
)

type double()(
	Size 12
)

type const()(
	State Static
)

type constexpr()(
	State Static
)

type export()()

export optimized func main,

$mod optimized(
	$pattern (
		if (i:ID == "ldr")(
			if (i:(Parameters:(0:Flags)) & Flag:_Register_)(
				if (i:(Parameters:(1:Name)) == "0")(
					i:(Parameters:1) = i:(Parameters:0),
					i:ID = "^"
				)
			)
		)
	)
)