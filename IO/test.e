type system,

system sys,
system Info,
system OS,

$if (sys:(Info:OS) == "win32")(
	using "cstd.e"
)

$if (sys:(Info:OS) == "unix")(
	using "gstd.e"
)

export func main()(
	print("Hello World!")
)