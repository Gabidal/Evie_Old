# GAC
GAS Compiler made in c++

This is the Documentary of the GAS for the time being.
Inturduction:
  GAS is a simple but powerfull programming language.
  It stand's between C and assembly.
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
  Variables in GAS are pretty straight foward.
  To make a Variable in GAS type this:
    var name = 123
  That is how you make a variable named "name" and the value of it is 123.
  
  
Strings:
  To make a string is the same as making a Variable. Just type:
    str name = "bananas"
  And that makes you a string called by "name" and it contains that bananas word init.
  You can also set to string's and then later overwrite the other string with the other:
    str banana = "bananas"
    str apple = "apples"
    gout %banana %banana.size
  Will print out "bananas"
  But if you do this:
    banana = apple
    gout %banana %banana.size
  Will print out "apples"
  

Functions:
  to make a function just type first this:
    func 
  That indicates that youre now making a function.
  Then to add parameter's type a space and then type the name of the parameter.
    func apple a b c d e f g 
  That makes you a functon named apple
  And has 7 parameters called a, b, c, d, e, f, g.
  Remember to put "ret" word for the function indicating when the function is ended.


Struct's:
  Struct's are super simple.
  they work like in C.
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
  Math is pretty straight foward.
  to use it use first some variable. Lets make a variable named: a.
    var a = 0
  then let's make more:
    var b = 1
    var c = 2
  And now let's use the + to make summation between b and c:
    a = b + c
  That's it!
  Same is for subtraction multiplition and division.
  
  
Multi File:
  To include / import more files to youre project, just type in the start of the file:
  use bananas.g
  and that will do it!
  
  
The STD lib
  The STD.g is like other's it just makes youre life easier:
     str abc = "bananas"
     gout abc abc.size
   Will for example print out the word "bananas".
   But! I need wolunteer's to help me with this STD.g lib! Same goes with this documentation.
   
   
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
   As you can see these % mark's are only when i want to call for the function i have made it will give the function parameter's as pointer's so that the gout will get the abc text not the name parameter's text.
   
   
 Array:
   To make an array do as same as making a variable ynly switch the = to : and the value is then the initial size of the array youre making.
     var abc : 123
   Will make a array named abc and it's length is 123 variables.
   To acces or modify these Array's just write:
     abc : 2 = 123
   Will put number 123, into abc.at(2).
     a = abc : 2
   Will put to variable a, number at abc.at(2)
 
 If Elses:
   To make an condition do this:
     var a = 2
     var b = 3
     if a < b
       gout %a %a.size
     else
       gout %b %b.size
     end
   i'm pretty shure that i dont need to tell you what is happening here!?
   
   
 
