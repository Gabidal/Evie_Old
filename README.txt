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

-4. Struct's.

-5. Math.

-6. Multi file Projects.

-7. The STD.

-8. Pointer's

-9. Array's

-10. If elses.


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
    gout %banana %banana.size
  Will print out "bananas"
  But if you do this:
    banana = apple
    gout %banana %banana.size
  Will print out "apples"
  

Functions:
  to create a function just type:

    func 

  That indicates that you are creating a function.
  Then, to add parameter's, type a space followed by the name of the parameter.
    func apple a b c d e f g 
  That leaves you with a functon named apple
  Which has 7 parameters called a, b, c, d, e, f, g.
  Remember to put "ret" word for the function indicating that the function is ended.


Struct's:
  Struct's are super simple.
  The way they work is similiar to how struct's work in C.
  just type:

    type fruit
      var sugarProsent = 0
      var weight = 0
    ;


  That makes a Struct named fruit.
  And this Fruit struct has two variables init sugarProsent and weight.
  To use them you need to make a new one, for example:
    new fruit banana
  That makes a new Struct named banana that has the same variables inside as the fruit struct.


Math:
  Math is pretty straightforward.
  to use it, you first need a variable. Lets make a variable named: a.

    var a = 0

  then let's make more:

    var b = 1
    var c = 2

  And now let's use the + to count the sum between b and c:

    a = b + c

  That's it!
  Same works for substraction multiplication and division.
  
  
Multi File:

  To include / import more files to youre project, just type in the start of the file:

  use bananas.g

  and that will do it!
  
  
The STD lib
  The STD.g is like other's. It just makes your life easier:

     str abc = "bananas"
     gout abc abc.size

   Will for example print out the word "bananas".
   But, this is still WIP. So I need volunteers to help me with developing this STD.g lib further! 
   
   
 Pointer's:
   To use a pointer do something like this for example:

     var a = 123
     str abc = "1234567890"
     func print name size
       gout name size
     ret
     
     func main
       print %abc %abc.size
     ret

   As you can see these % mark's are only when you want to call for the function. It is made to give the function parameter's as pointer's so that the gout will get the abc text not the name parameter's text.
   
   
 Array:
   To make an array do as same as making a variable ynly switch the = to : and the value is then the initial size of the array your making.

     var abc : 123

   Will make a array named abc and it's length is 123 variables.
   To acces or modify these Array's just write:

     abc : 2 = 123

   Will put number 123, into abc.at(2).

     a = abc : 2

   Will put to variable a, number at abc.at(2)
 
 If Elses:
   To create an If Else condition do this:
  
   var a = 2
     var b = 3
     if a < b
       gout %a %a.size
     else
       gout %b %b.size

     end
 
   
   
 
