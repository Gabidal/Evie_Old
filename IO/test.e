using "cstd.e"

type system

system sys
system Info
system OS

$if (sys:(Info:OS) == "win32")(
	using "win32_std.e"
)

$if (sys:(Info:OS) == "unix")(
	using "unix_std.e"
)

export func main()(
	print("Hello World!")
)