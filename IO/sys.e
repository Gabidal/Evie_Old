type _SYSTEM_

_SYSTEM_ _SYS_
_SYSTEM_ _INFO_

_SYSTEM_ _SOURCE_FILE_
_SYSTEM_ DESTINATION_FILE_
_SYSTEM_ _OS_
_SYSTEM_ _ARCHITECTURE_ 
_SYSTEM_ _OBJ_TYPE_
_SYSTEM_ _BITS_MODE_

$if (_SYS_:(_INFO_:_OS_) == "win32")(
	$use "win32.asm"
)

$if (_SYS_:(_INFO_:_OS_) == "unix")(
	$use "unix.asm"
)
