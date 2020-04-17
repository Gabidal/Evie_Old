type system,

system sys,
system Info,

system Static,
system Virtual,
system Hidden,
system export,
system import,
system loyal,

system Source_File,
system Destination_File,
system OS,
system Architecture,
system Obj_Type,
system Bits_Mode,


$if (sys:(Info:OS) == "win32")(
	using "win32.e"
)

$if (sys:(Info:OS) == "unix")(
	using "unix.e"
)
