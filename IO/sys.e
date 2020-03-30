type system,

system sys,
system Info,

system Static,
system Virtual,

system Source_File,
system Destination_File,
system OS,
system Architecture,
system Obj_Type,
system Bits_Mode,

type IR,
type Token,
type List,
type Integer,
type Flag,

IR List IN,
Integer i,


IR ID,
Token List Parameters,

Token Flags,
Token Name,
Token Type,
Flag _Register_,

$if (sys:(Info:OS) == "win32")(
	using "win32.e"
)

$if (sys:(Info:OS) == "unix")(
	using "unix.e"
)
