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
-multiline math register handle fix.
-removed reduntant register abuse.


## Manual

### Type
Types are the biggest differences between GAS and Evie.
#### Syntax:
```
    type [name]()(
        [feature] [number]
    )
    
    [type_name] [new_defining_class_name] 
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
[./]Evie[.exe] [input filename] [output filename] -[OS] -[architecture] -[Flag] -[Force maximum bit size]
```

### Future of Evie

Atm, just fixes.
Then the FPU support and new type feature: ```[precision] [number of decimal's]```.