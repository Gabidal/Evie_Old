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
Beta 2.0.0 bringes new Lexer, Parser, Back-end.
More flexible than ever.

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