[![Total alerts](https://img.shields.io/lgtm/alerts/g/Gabidal/Evie.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Gabidal/Evie/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Gabidal/Evie.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Gabidal/Evie/context:cpp)
# Evie- lang

### Catalog:
- #### Manual
    - ##### Type.
    - ##### Base type.
    - ##### Static member.
    - ##### Member function.
    - ##### Function.
    - ##### Static funciton.
    - ##### If statement.
    - ##### Loop.
    - ##### File include.
    - ##### Manual header info construction.
    - ##### Asm file including.
    - ##### VTC.
    - ##### Array.
    - ##### Preprosessor.
    - ##### Arguments.
    - ##### Notices!

## Manual

### Type
#### Types are like classes in any other programming language.
#### Syntax:
```
    type Foo{
        int X = 1
        int y = 2
    }
```

### Base type
#### In Evie you can make your own base types
#### Syntax:
```
    type Foo{
        size = 4 #this 4 represent's bits size of this base type
        format = integer #this can be 'integer' or 'decimal'
    }
```

#### Oh did i mention you can type basically anything into the type's initialization, 
#### it all gets transformed into constructor code nonetheless.
#### Syntax:
```
    type Foo{
        int X = 1
        int y = 2
        call_something(X, Y)
        if (X == 2){
            X = 3
        }
    }
```

### Static member
#### Syntax:
```
    type Foo{
        static int X = 1
        static int Y = 2
        int Z = 3
    }

    int baz(){
        return Foo.X + Foo.Y
    }
```

### Member function
#### Syntax:
```
    type Foo{
        int X = 1
        int Fuz(int something){
            return something + X
        }
    }

    int Foo.Baz(){
        return X
    }
```

### Function
#### the 'func' keyword is same as C++ 'void'.
#### Syntax:
```
    int Calculate(int param1, int param2){
        return param1 + param2
    }

    func Foo(int param1, int param2){
        int useless = param1 - param2 + Calculate(param1, param2)
    }
```

### Static function
#### Syntax: 
```
    type foo{
        static int Fuz(int x, int y){
            return x + y
        }
    }

    int baz(){
        return foo.Fuz(1, 2)
    }
```

### If statement
#### Syntax:
```
    int Foo(){
        int i = 1
        int j = 2
        if (i == j){
            return 0
        }
        else (i < j){
            return 1
        }
        else{
            return j
        }
    }
```

### Loop
#### Syntax:
```
    int Increment(int x){
        return x + 1
    }

    int Foo(){
        int x = 0
        while (int i = 0; i < 10; i++){
            x = Increment(x)
        }
        if (x == 10){
            while (x > 0){
                x--
            }
        }
        return x
    }
```

### File include
#### Evie can also include .lib files, .elf files, URL files, .dll files, git repos, .asm files.
#### Evie can automatically construct header file information for the included file like lib/elf/dll/asm
#### If Evie doesn't find the wanted file in the included repo, then Evie will try to use 'Make all' or 'Make -B' to build the repo.
#### To get the wanted repo file.
#### Although in some situations you, the user must you're self give Evie header information about the content of that included file.
#### Syntax:
```
    use "some_file.e"
    use "some_lib.lib"
    use "some_elf.elf"
    use "https://some_URL/file_x.e/dll/lib/elf/asm"
    use "some_dll.dll"
    use "https://github.com/some_user/some_repo/some_util.e/dll/lib/elf/asm"
    use "https://bigbucket.com/some_user/some_repo/make_file_requiring_lib.lib"
    use "some_ams.asm"

    #utilization of included files here. :D
```

### Manual header info construction
#### Syntax:
```
    use "hard_to_automatically_construct_include_binary.lib/elf/dll/asm"

    import int manually_constructed_function(int, int)
```

### Asm file including
#### When including .asm files, the included file must begin with the following comment: '#analyze'.
#### Also make shure that you're .asm file is written in GNU-assembler syntax.

### VTC
#### The VTC stands for Virus Total Check.
#### It means that Evie will check all files that come from outside world with VTC.
#### Evie also check's the generated output binary with VTC.
#### Of course, for this to work you need to pass to Evie when builing your virus total API-key.
#### Syntax:
```
    ./Evie -in some_file.e -vt [API_KEY_HERE]
```

### Array
#### Syntax:
```
    int Baz(){
        #1D arraysa
        int ptr Array1 = allocate(int.size * 10)
        Array1[0] = 123
        return Array[0]
    }

    int Foo(){
        #2D arrays
        int ptr Array1 = allocate(int.size * 100)
        Array1[1, 2] = 123
        return Array[1, 2]
    }
```

### Preprosessor
#### The Evie preprosessor gives us these to work with:
- ##### SOURCE_FILE
- ##### DESTINATION_FILE
- ##### OS
- ##### ARCHITECTURE
- ##### FORMAT
- ##### BITS_MODE
- ##### true
- ##### false


### Arguments
##### -in [relative path/source file]
##### -out [relative path/output file name]
##### -os [target operating system (win32/unix)]
##### -host [the host operating system (win32/unix)]
##### -arch [output assembly type (x86/arm)]
##### -lib [relative path/lib name]
##### -repo_dir [relative/absolute path for saving git repos]
##### -mode [bit mode for assembly output (32/64)]
##### -vt [virus total API-key]
##### -f [supported output file formats are:
#####     exe(executable (works for unix as well)),
#####     lib(static lib),
#####     dll(dynamic library (support is not made yet!))
##### ]
##### -debug [ supported debug symbol types:
#####     dwarf2
##### ];



### Notices
##### If you are in Linux, then you need to install curllib to Evie to work :D
##### I recommend you to install "sudo apt install libcurl4-openssl-dev"
##### G++
##### Make
##### GDB