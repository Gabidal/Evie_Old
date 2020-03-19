using "cstd.e"

Inter check_system_OS(
	ptr $sys.Info.OS
	if (sys.Info.OS == "win32")(
		using "win32_std.e"
	)
	if (sys.Info.OS == "unix")(
		using "unix_std.e"
	)
)

Inter main(
	check_system_OS
)

export func main()(
	print("Hello World!")
)