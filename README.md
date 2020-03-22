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
- #### Future of Evie




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

## Manual

### Type
Types are the biggest differences between GAS and Evie.
#### Syntax:
```
    type [name]()(
        [feature] [number]
    )
    
    [type_name] [new_defined_object_Name] 
```

### Function
The functions are nontype.
#### Syntax:
```
func [name] ([parameter,s])(
    [code]
)
```

### Condition
Notice how the condition does not have else if's nor else's.
#### Syntax:
```
if ([condition])(
    [code]
)
```

### Loop
It loop's until the condition it is given proves wrong.
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
Like other languages.
#### Syntax:
```
[name] [operator] [name]
```

### Array
Array's are actually just normal operator's.
#### Syntax:
```
[name]:[offsetting name]
```

### Argument's

#### Synatx:
```
[./]Evie[.exe] -in [input filename]  -out [output filename] (-lib [output type {obj, exe, li, so, etc}] == not a must) -os [OS] -arch [architecture] (-mode [bits mode] == not a must)
```

### Future of Evie

Atm, just fixes.
Then the FPU support and new type feature: ```[precision] [number of decimal's]```.