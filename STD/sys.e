if (OS == "win"){
	if (ARCHITECTURE == "x86"){
		use "https://github.com/lehtojo/vivid/Vivid/libv/windows_x64/console.asm"
		use "https://github.com/lehtojo/vivid/Vivid/libv/windows_x64/math.asm"
		use "https://github.com/lehtojo/vivid/Vivid/libv/windows_x64/memory.asm"
		use "https://github.com/lehtojo/vivid/Vivid/libv/windows_x64/system.asm"
		use "Win/File.e"
	}
}

if (OS == "unix"){
	if (ARCHITECTURE == "x86"){
		use "https://github.com/lehtojo/vivid/Vivid/libv/linux_x64/memory.asm"
		use "https://github.com/lehtojo/vivid/Vivid/libv/linux_x64/math.asm"
		use "https://github.com/lehtojo/vivid/Vivid/libv/linux_x64/console.asm"
		use "https://github.com/lehtojo/vivid/Vivid/libv/linux_x64/system.asm"
	}
}