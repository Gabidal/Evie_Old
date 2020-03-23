using "cstd.e"

type system,

system Lexer,
system Parser,
system Selector,

system Name,
system Flags,


system _Number_ 
system _External_
system _Type_
system _Function_
system _Array_
system _Condition_ 
system _Operator_
system _Returning_ 
system _Call_
system _Parameter_
system _Parenthesis_
system _Constructor_
system _Register_
system _Inheritting_
system Task_For_Returning
system Task_For_Type_Address_Basing
system Task_For_Type_Address
system Task_For_Moving_Parameter
system Task_For_Offsetting
system Task_For_Remainder
system Task_For_General_Purpose
system Task_For_Floating_Math
system _Need_For_Space_
system _Generated_
system _Pointting_
system _Array_
system _Giving_Address_
system _String_


"int a = 0"
$func use_xor (int, text, operator, any) (
	$if (any:Flags == _Number_) (
		$if (operator == "=") (
			$if (text == _Defined_) (
				operator:Name = "^"
				any = text
			)
		)
	)
)

export func main()(

	int a = 0
	return a
)