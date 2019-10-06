# GAC
GAS Compiler made in c++

This is the documentation for GAS.
Introduction:
  GAS is a simple but powerful programming language.
  It aims to stand between C and assembly.
;

Manual:

-1. Variables.

-2. Strings.

-3. Functions.

-4. Types.

-5. Math.

-6. Multi file Projects.

-7. The STD.

-8. Pointer's

-9. Array's

-10. If elses.

-11. loops.

-11. Using the actual GAS.


MANUAL:

Variables:
  Variables in GAS are quite straightforward.
  To make a Variable in GAS all you need to do is type:

    var name = 123

  That is how you create a variable named "name" and set formentioned variables value to 123.
  
  
Strings:
  To make a string is very similiar to making a Variable:

    str name = "bananas"

  And that makes you a string named "name" which contains that bananas word init.
  You can also set two string's and later in the code overwrite the other string with the other:

    str banana = "bananas"
    str apple = "apples"
    gout(banana)

  Will print out "bananas"
  But if you do this:

    banana = apple
    gout(banana)

  Will print out "apples"
  

Functions:
  to create a function just type:

    func [name] ([parameter], [second parameter])
    (
      #code....
    )

  That indicates that you are creating a function.


Types:
  Types are super simple.
  The way they work is similiar to how classes work in C++.
  just type:

    type fruit()
    (
      var sugarProsent = 0
      var weight = 0
      func init(this, a, b)
      {
        -> sugarProsent = a
        -> weight = b
      }
    )

  The parameter named [this] will tell the GAS compiler to reserve one more place for allocated type address. 

  That makes a Type named fruit.
  And this Fruit type has two variables init sugarProsent and weight.
  To use them you need to make a new one, for example:
    new fruit banana
  This will allocate memory on runtime.


Math:
  Math is pretty straightforward.
  to use it, you first need a variable. Lets make a variable named: a.

    var a = 0

  then let's make more:

    var b = 1
    var c = 2

    a = b + c * a - c / b

  That's it!
  
  
Multi File:

  To include / import more files to youre project, just type in the start of the file:

  use bananas.g

  and that will do it!
  
  
The STD lib
  The STD.g is like other's. It just makes your life easier:

     str abc = "bananas"
     gout abc

   Will for example print out the word "bananas".
   But, this is still WIP. So I need volunteers to help me with developing this STD.g lib further! 
   
   
Pointer's:
 To use a pointer do something like this for example:

 [(Pointers are still in under developing. So if you have some cool suggestion join the GAS community and say it :D )]

     var a : 10
     var b = 0
     func doSomethigPlz(&list)
     (
       var a = list + 1
     )
     
     func main()
     (
       var a : 12
       doSomethigPlz(a)
     )

   
Array:
   To make an array do as same as making a variable only switch the = to : and the value is then the initial size of the array your making.

     var abc : 123
     var a = 321
     var b = 1

   Will make a array named abc and it's length is 123 variables.
   To acces or modify these Array's just write:

     abc : b = a

   Will put number from variable a, into abc.at(variable b).

     a = abc : b

   Will put to variable a, number at abc.at(variable b)
 
 
If Elses:
  To create an If Else condition do this:
  [( Yeah if'n elses do not have the () thing :D )]
  
     var a = 2
     var b = 3
     str banana = "bananas!"
     str apple = "apples!"

     if a < b
     (
       gout(banana)
     )
     else
     (
       gout(apple)
     )
 
   
Loops:
  in GAS there is only one looper XD.
  while ([variable start] : [variable to pursue])
  (
    #code that loops....
  )
  the Variable [start] will increase until is same as the goal/end Variable.

Linux:
Using the actual GAS.
First do:

    sudo apt install yasm
  
then go to your folder where the GAS runnable is:
    
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
 
 

Windows:
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
