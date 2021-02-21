if (OS == "win"){
	if (ARCHITECTURE == "x86"){
		use "win32.asm"
	}
}

if (OS == "unix"){
	if (ARCHITECTURE == "x86"){
		use "unix.asm"
	}
}
