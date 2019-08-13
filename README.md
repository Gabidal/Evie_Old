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


MANUAL (-1.):
Variables:
  Variables in GAS are pretty straight foward.
  To make a Variable in GAS type this:
    var name = 123
  That is how you make a variable named "name" and the value of it is 123.
  
Strings:
  To make a string is the same as making a Variable. Just type:
    str name = "bananas"
  And that makes you a string called by "name" and it contains that bananas word init.

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

