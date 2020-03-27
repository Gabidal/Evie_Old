use "cstd.e"

$pattern (
	if (IN:(i:ID) == "lda")(
		if (IN:(i:(Parameters:(0:Flags))) == "_Register_")(
			if (IN:(i:(Parameters:(1:Name))) == "0")(
				IN:(i:(Parameters:(1))) = IN:(i:(Parameters:(0))),
				IN:(i:ID) = "^"
			)
		)
	)
)

func main()(
	return 0
)