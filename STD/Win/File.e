static std{
	int GENERIC_WRITE = 1073741824
	int GENERIC_READ = 2147483648
	
	int FILE_SHARE_NONE = 0
	int FILE_SHARE_READ = 1
	int FILE_SHARE_WRITE = 2
	int FILE_SHARE_DELETE = 4
	
	int CREATE_NEW = 1
	int CREATE_ALWAYS = 2
	int OPEN_EXISTING = 3
	int OPEN_ALWAYS = 4
	int TRUNCATE_EXISTING = 4
	
	int FILE_ATTRIBUTE_NORMAL = 128
	int FILE_ATTRIBUTE_FOLDER = 16
	
	int MAXIMUM_PATH_LENGTH = 260
	
	int ERROR_INSUFFICIENT_BUFFER = 122
	int MINIMUM_PROCESS_FILENAME_LENGTH = 50
	
	import plain char ptr FindFirstFileA(char ptr filename, FileIterator iterator)
	import plain char ptr FindNextFileA(char ptr handle, FileIterator iterator)
	import plain char ptr CreateFileA(char ptr filename, int access, int share_mode, char ptr security_attributes, int creation_disposition, int flags_and_attributes, char ptr template)
	import plain char ptr GetCommandLineA()
		   
	import plain bool GetFileSizeEx(char ptr handle, long ptr size)
	import plain bool WriteFile(char ptr handle, char ptr buffer, long size, long ptr written, char ptr overlapped)
	import plain bool ReadFile(char ptr handle, char ptr buffer, long size, long ptr read, char ptr overlapped)
	import plain bool CloseHandle(char ptr handle)
		   
	import plain int GetFileAttributesA(char ptr path)
		   
	import plain long GetLastError()
	import plain long GetEnvironmentVariableA(char ptr name, char ptr buffer, long size)
	import plain long GetModuleFileNameA(char ptr module, char ptr buffer, long size)


	type Char_260{
		size = 260
	}

	type Char_14{
		size = 14
	}

	type FileIterator {
		int attributes
		long creation_time
		long last_access_time
		long last_write_time
		long file_size
		long reserved
		Char_260 filename
		Char_14 alternate_filename
		int file_type
		int creator_type
		short finder_flags
	}



}