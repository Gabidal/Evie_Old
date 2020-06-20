type system

system sys
system Info

system Source_File
system Destination_File
system OS
system Architecture
system Obj_Type
system Bits_Mode

$if (sys:(Info:OS) == "win32")(
	$use "win32.asm"
)

$if (sys:(Info:OS) == "unix")(
	$use "unix.asm"
)
