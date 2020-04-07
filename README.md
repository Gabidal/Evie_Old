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
``` link /NXCOMPAT /DYNAMICBASE "glfw3.lib" "OpenGL32.lib" "kernel32.lib" "user32.li
b" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.
lib" "odbccp32.lib" /DEBUG /MACHINE:X86 /INCREMENTAL /SUBSYSTEM:CONSOLE /MANIFESTUAC:"level='asInvoker' uiAccess='false'
" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1  test.asm.obj /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\u
m\x86" OpenGL32.lib /entry:main /out:test.asm.exe /libpath:"C:\Program Files (x86)\Microsoft Visual Studio\2019\Communit
y\VC\Tools\MSVC\14.25.28610\lib\x86" vcruntime.lib /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\ucr
t\x86" ucrt.lib```

- ###### Evie can now use OpenGL 


Beta 2.1.64 added:

- ###### Evie now supports global variables.

- ###### Evie now supports the linking inline.
Use OpenGL32.lib as a -lib argument, on windows.
```-in IO/test.e -out IO/test.asm -lib OpenGL32.lib -os win32 -arch x86 -mode 4 -debug dwarf2```
Sorry for Linux users, u have to use ur skills, until i have added a template for linux too...

## Manual

### Type
###### Types are the biggest differences between GAS and Evie.
#### Syntax:
```
    type [name]()(
        [feature] [number]
    )
    
    [type_name] [new_defined_object_Name] 
```

### Function
###### The functions are nontype.
#### Syntax:
```
func [name] ([parameter,s])(
    [code]
)
```

### Condition
###### Notice how the condition does not have else if's nor else's.
#### Syntax:
```
if ([condition])(
    [code]
)
```

### Loop
###### It loop's until the condition it is given proves wrong.
#### Synatx:
```
while ([condition])(
    [code]
)
```

### Multi-file

#### Syntax:
```
using "[folder/filename]"
```

### Math
###### Like other languages.
#### Syntax:
```
[name] [operator] [name]
```

### Array
###### Array's are actually just normal operator's.
#### Syntax:
```
[name]:[offsetting name]
```

### Argument's

#### Synatx:
```
[./]Evie[.exe] -in [input filename]  -out [output filename] (-lib [output type {obj, exe, li, so, etc}] == not a must) -os [OS] -arch [architecture] (-mode [bits mode] == not a must)  (-debug [type(for example dwarf2)] = not a must)
```

### Preprosessor

###### Atm there is only preprosessor conditional if's

###### Also the preprosessor gives us some goods: 
```
system sys,
system Info,

system Source_File,
system Destination_File,
system OS,
system Architecture,
system Obj_Type,
system Bits_Mode,
```

###### These are some information gathered from the argument's given to Evie.

#### Syntax:
```
$if ([Condition (Use only constant values!!)])(
    [The code to be injected if the condition is true]
)
```

### Future of Evie

###### Atm, just fixes.

###### Then the FPU support and new type feature: ```[precision] [number of decimal's]```.