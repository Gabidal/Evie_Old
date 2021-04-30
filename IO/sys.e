if (OS == "win"){
	if (ARCHITECTURE == "x86"){
		use "win32.asm"
	}
}

if (OS == "unix"){
	if (ARCHITECTURE == "x86"){
		#use "unix.asm"
		use "https://github.com/lehtojo/vivid/blob/transition/Vivid/libv/linux_x64/memory.asm"
		use "https://github.com/lehtojo/vivid/blob/transition/Vivid/libv/linux_x64/math.asm"
		use "https://github.com/lehtojo/vivid/blob/transition/Vivid/libv/linux_x64/console.asm"
		use "https://github.com/lehtojo/vivid/blob/transition/Vivid/libv/linux_x64/system.asm"
	}
}
