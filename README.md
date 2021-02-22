[![Total alerts](https://img.shields.io/lgtm/alerts/g/Gabidal/Evie.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Gabidal/Evie/alerts/)
# Evie- lang

### Catalog:
- #### New's
- #### Manual
    - ##### Types.
    - ##### Function.
    - ##### Condition.
    - ##### Loop.
    - ##### Multi-file.
    - ##### Math.
    - ##### Array.
    - ##### Arguments.
    - ##### Preprosessor.
    - ##### Docker.
    - ##### Future of Evie




## New's
Beta 2.0.0 brings new Lexer, Parser, Back-end.
More flexible than ever.

Beta 2.0.8 fixed:
- ###### multiline math register handle fix.
- ###### removed reduntant register abuse.


Beta 2.1.2 fixed:
- ###### Stackframe added.
- ###### Parameter order reversed.
- ###### Stupid/Ridiclius stackOffset's removed.
- ###### Tooken Registers from tokens away.


Beta 2.1.4 fixed:
- ###### Makefile updated.


Beta 2.1.6 fixed:
- ###### If's.
- ###### AL & AH had same ID.
- ###### Now calling a exported function works :D.


Beta 2.1.9 fixed:
- ###### Exporting is now

From:
```
    export main()(..)
```

To:
```
    export func main()(..)
```
- ###### Also Exporting has it's own type class in CSTD.e .


Beta 2.1.10 fixed:
- ###### Parameters didnt have stackframe.

Beta 2.1.11 fixed:
- ###### Fixed returning register.

Beta 2.1.12 added:
- ###### Added pointters (experimental)

Beta 2.1.16 added:
- ###### Added Scaler function to fix some scaling problems.

Beta 2.1.20 fixed:
- ###### Fixed stack register abuse.

Beta 2.1.30 added:
- ###### Added Linux file linking.

Beta 2.1.40 added:
- ###### Added post prosessor. See <sys.e> for a example.

Beta 2.1.46 added:
- ###### Boost lib to imrpove your code output.

Beta 2.1.51 fixed:
- ###### Fixed stupid parameter pusher.
- ###### Added a new pattern into boost.e .

Beta 2.1.62 added:
- ###### Added a new pattern to improve math.

Beta 2.1.63 added:
- ###### Added new link method:
```
link /NXCOMPAT /DYNAMICBASE "glfw3.lib" "OpenGL32.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEBUG /MACHINE:X86 /INCREMENTAL /SUBSYSTEM:CONSOLE /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1  test.asm.obj /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x86" OpenGL32.lib /entry:main /out:test.asm.exe /libpath:"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.25.28610\lib\x86" vcruntime.lib /libpath:"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.26.28801\lib\x86" /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\ucrt\x86" ucrt.lib
```
- ###### Evie can now use OpenGL 


Beta 2.1.64 added:

- ###### Evie now supports global variables.
- ###### Evie now supports the linking inline.

Use OpenGL32.lib as a -lib argument, on windows.
```
-in IO/test.e -out IO/test.asm -lib OpenGL32.lib -os win32 -arch x86 -mode 4 -debug dwarf2
```
Sorry for Linux users, u have to use ur skills, until i have added a template for linux too...

Beta 2.1.68 added/fixed:
- ###### added loyal keyword, use this if you dont want to clean the called functions parameters from stack.
- ###### rewamped the whole typing system from string into vector strings so that you can inherit literally unlimited amount of types.


Beta 2.1.82 fixed:
- ###### cache variable inherit numbr and thus crash.
- ###### optimized some array output.

Beta 2.1.103 fixed:
- ###### Register selection is now improved.

Beta 2.1.104 fixed:
- ###### Safe doesnt yell at everything enymore.
- ###### Added line number into token info at Safe, so now you can find your problems in life :P


Beta 2.1.105 added:
- ###### Added C like array pointting:"int a[0] = 123".

Beta 2.1.121 added/fixed:
- ###### Fixed some issues with the docker system. Now using elf files should be working regardles the order of files.
- ###### Now you dont even have to make header file to every elf file (or lib/dll in future) you just need to make one header file named "general.[a-z]".


Beta 2.1.222 added:
- ###### New Safe method into Safe.cpp, named: Safe_Calling(Token* t);
- ###### Evie now should be able to assist you on right function calling's.


Beta 2.1.223 added:

- ###### Finally the member support is here!



## Manual

### Type
###### Types are the biggest differences between GAS and Evie.
#### Syntax:
```
    type [name](){
        [feature] [operator(=)] [number]
        [type] [name]
    }
    
    [type_name] [new_defined_object_Name] 
```


### Function
###### The functions are nontype.
#### Syntax:
```
[return type] [name] ([parameter(s)], ..){
    [code]
}
```


### Condition
###### Notice how the condition does not have else if's nor else's.
#### Syntax:
```
if ([condition]){
    [code]
}
```


### Loop
###### It loop's until the condition it is given proves wrong.
#### Synatx:
```
while ([condition]){
    [code]
}

while ([set], [condition], [footer]){
    [code]
}
```


### Multi-file
#### Syntax:
```
use "[folder/filename]"
```
#### You can also give Evie ASM/OBJ/ELF/LIB/URL files!


### Math
###### Like other languages.
#### Syntax:
```
[value] [operator] [value]
```

### Array
###### Array's are actually just normal operator's.
#### Syntax:
```
[array name][[offsetter]]
```

### Argument's
#### Synatx:
```
[./]Evie[.exe] -in [input filename]  -out [output filename] (-lib [output type {obj, exe, li, so, etc}] == not a must) -os [OS] -arch [architecture] (-mode [bits mode] == not a must)  (-debug [type(for example dwarf2)] = not a must)
```

### Preprosessor
###### Atm there is only preprosessor conditional if's
###### Also the preprosessor gives us some goods: 
- ###### SOURCE_FILE
- ###### DESTINATION_FILE
- ###### OS
- ###### ARCHITECTURE
- ###### FORMAT
- ###### BITS_MODE
- ###### true
- ###### false

###### Use these preprosessor variables like this:
```
if (OS == "win32"){
    [code if the condition yelds true]
}
```

### Docker
###### Docker is the next generation of file handling in Evie.
###### Docker can understand elf, as well as lib & dll files in future.
###### "But how does Evie know what function is what", you might ask.
###### Evie has a built in REGEX support. Meaning that you can just give Evie the type of inheritting and the REGEX string it references, in the header file.
###### Example:

```
[loyal std = "_(\w*@*)*"]
```

###### The above code creates a new object named (std) which inherits the (loyal) keyword.
###### The loyal keyword implies that the function cleans its stack on its own, not the user.
###### Now, the object std is set to the value of the string ("_(\w*@*)*").
###### That string is in REGEX syntax.
###### The elf(+lib & dll in future) is given to Docker so that it can find the corresponding header and then sets every function it finds, that has corresponding REGEX string, to the same inheriting features that (std) has.

### Templates
###### Example:
```
use "cstd.e"

func foo(type ptr a, type ptr b, int size){
    while(int i = 0; i < size; i++){
        a[i] = b[i]
    }
}
```
###### Evie will copy the funciton into a new funciton but with the given parameter types.

### Future of Evie
###### Atm, just making the Evie engine 3.0. 