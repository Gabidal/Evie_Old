type _SYSTEM_

_SYSTEM_ _SYS

_SYSTEM_ SOURCE_FILE_
_SYSTEM_ DESTINATION_FILE_
_SYSTEM_ OS_
_SYSTEM_ ARCHITECTURE_ 
_SYSTEM_ OBJ_TYPE_
_SYSTEM_ BITS_MODE_

if (_SYS.OS_ == "win32"){
	use "win32.asm"
}

if (_SYS.OS_ == "unix"){
	use "unix.asm"
}
