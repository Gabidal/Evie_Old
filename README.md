# GAS
GAS Compiler made in c++

This is the documentation for GAS.
Introduction:
  GAS is a simple but powerful programming language.
  It aims to stand between C and assembly.
;

# Manual:

 - ### 1. Variables.
 
 - ### 2. Strings.

- ### 3. Functions.

- ### 4. Types.

- ### 5. Math.

- ### 6. Multi file Projects.

- ### 7. The STD.

- ### 8. Pointer's

- ### 9. Array's

- ### 10. If elses.

- ### 11. loops.

- ### 11. Using the actual GAS.


## MANUAL:

#### Variables:
  Variables in GAS are quite straightforward.
  To make a Variable in GAS all you need to do is type:

```Cpp
    var name = 123
  ```
  That is how you create a variable named "name" and set formentioned variables value to 123.

  
#### Strings:
  To make a string is very similiar to making a Variable:

```Cpp
    var name = "bananas"
  ```
  And that makes you a string named "name" which contains that bananas word init.
  You can also set two string's and later in the code overwrite the other string with the other:

```Cpp
    var banana = "bananas"
    var apple = "apples"
```

#### Functions:
  to create a function just type:

```Cpp
    func [name] ([parameter], [second parameter], [etc...])
    (
      ...
    )
  ```
  That indicates that you are creating a function.
  And add the ( ... ) gives the function the code for it,
  if you want to make just a prototype of a function do this:
    
```Cpp
    func [name] ([etc..])
  ```

#### Types:
  Types are super simple.
  The way they work is similiar to how struct's work in C.
  just type:

```Cpp
    type fruit()
    (
      var sugarProsent = 0
      var weight = 0
    )
  ```

  That makes a Type named fruit.
  And this Fruit type has two variables init sugarProsent and weight.
  To use them you need to make a new one, for example:
    new fruit banana
  This will allocate memory on runtime.


#### Math:
  Math is pretty straightforward.
  to use it, you first need a variable. Lets make a variable named: a.

```Cpp
    var a = 0
 ```
  then let's make more:
  
```Cpp
    var b = 1
    var c = 2

    a = b + c * a - c / b
  ```
  
  That's it!
  
  
#### Multi File:

  To include / import more files to youre project, just type in the start of the file:

```Cpp
  using "std.g"

  and that will do it!
 ```
  
#### The STD lib
  The std.g is like other's. It just makes your life easier:

```Cpp
     var abc = "bananas"
     print(abc)
  ```
   Will for example print out the word "bananas".
   But, this is still WIP. So I need volunteers to help me with developing this STD.g lib further! 
   
   
#### Pointer's:
 To use a pointer do something like this for example:

- ###### [(Pointers are still in under developing. So if you have some cool suggestion join the GAS community and say it :D )]
```Cpp
     var a = malloc(40)
     func get_Next_Var(list)
     (
       return list : 4
     )
     
     func main()
     (
       var f = get_Next_Var(&a)
     )
```
   
#### Array:
   To make an array do as same as making a variable only switch the = to : and the value is then the initial size of the array your making.

```Cpp
     var a = malloc(123)
     var b = 1
  ```
   Will make a array named abc and it's length is 123 bits.
   To acces or modify these Array's just write:

```Cpp
     abc : b = a
  ```
   Will put number from variable a, into abc.at(variable b).

```Cpp
     a = abc : b
  ```
   Will put to variable a, number at abc.at(variable b)
 
 
#### If Elses:
  To create an If Else condition do this:
  
```Cpp
     var a = 2
     var b = 3
     var banana = "bananas!"
     var apple = "apples!"

     if (a < b)
     (
       print(banana)
     )
     else if ((a -1) < 0)
     (
       print(apple)
     )
     else
     (
       print("haha")
     )
 ```
#### Loops:
  in GAS there is only one looper XD.
```Cpp
     while ([as long as condition])
     (
          #code that loops....
     )
   ```
  Remember that no variables here are increasing/decreasing, 
  so you have to do it by youre self.

#### Linux:
Using the actual GAS.
First do:

    sudo apt install yasm
  
then go to your folder where the GAS executable is:
    
    cd bananas/GAS
    
There should be now the GAS itself and the *.g files as well.Then do this:
    
    chmod +x 0777 GAS
Then do this:

    ./GAS
    
This will launch the GAS compiler. After compiling you have the source file but with the *.asm marking at the end of the file name.
That is the output that GAS gave you.You need now to give it to yasm:
    
    yasm -f elf32 -o banana.o banana.asm
    
That will create the *.o file. Then you need to link it:

    ld -m elf_i386 -o banana banana.o
    
That will make it executable. Then do this:

    chmod +x 0777 banana
    
And then youre done! Now you can always run the script that you made in GAS. 

Just type:
    
    ./banana

And it will run :D
 
 

#### Windows:
First do:

    download yasm for windows 64
    download g++ for windows 64
  
then go to your folder where the GAS source code is:
    
    cd Bananas/GAS
    i686-w64-mingw32-g++ -o GAS.exe main.cpp
    
Then do this:

    GAS.exe
    
This will launch the GAS compiler. After compiling you have the source file but with the *.asm marking at the end of the file name.
That is the output that GAS gave you.You need now to give it to yasm:
    
    yasm -f win32 -o banana.exe banana.asm
    
That will make it executable.
And then youre done! Now you can always run the script that you made in GAS. 

Just type:
    
    banana.exe

And it will run :D
