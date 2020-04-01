#Boost variables:

type String,
type IR,
type Token,
type List,
type Integer,
Integer Flag,
Integer Stack_Offset,
String UID,

List IN,
Integer p,
Integer c,
Integer n,


IR ID,
List Parameters,

Token Flags,
Token Name,
Token Type,
Flag _Register_,
Flag _Number_,
Flag _External_,
Flag _Type_,
Flag _Function_,
Flag _Array_,
Flag _Condition_,
Flag _Operator_,
Flag _Returning_,
Flag _Call_,
Flag _Parameter_,
Flag _Parenthesis_,
Flag _Constructor_,
Flag _Register_,

Flag _Inheritting_,

Flag Task_For_Returning,
Flag Task_For_Type_Address_Basing,
Flag Task_For_Type_Address,
Flag Task_For_Moving_Parameter,
Flag Task_For_Remainder,
Flag Task_For_General_Purpose,
Flag Task_For_Floating_Math,

Flag _Need_For_Space_,
Flag _Generated_,

Flag _Pointting_,
Flag _Array_,
Flag _Giving_Address_,
Flag _String_,
Flag _Preprosessor_,
Flag _Skip_,


#This pattern checks if we can make "reg <- 0" into just "xor reg, reg".
$pattern (
	if (c:ID == "ldr")(
		if (c:(Parameters:(0:Flags)) & Flag:_Register_)(
			if (c:(Parameters:(1:Name)) == "0")(
				c:(Parameters:1) = c:(Parameters:0),
				c:ID = "^"
			)
		)
	)
)

#this pattern deletes reduntant savind/loading issues.
$pattern(
	if (c:ID == "=")(
		if (n:ID == "ldr")(
			if (c:(Parameters:(0:Name)) == n:(Parameters:(1:Name)))(
				if (c:(Parameters:(1:UID)) == n:(Parameters:(0:UID)))(
					c:Flags |= Flag:_Skip_,
					n:Flags |= Flag:_Skip_,
				)
			)
		)
	)
)

#this pattern deletes moving same reg into same reg.
$pattern(
	if (c:ID == "ldr")(
		if (c:(Parameters:(0:UID)) != "")(
			if (c:(Parameters:(0:UID)) == c:(Parameters:(1:UID)))(
				c:Flags |= Flag:_Skip_
			)
		)
	)
	if (c:ID == "=")(
		if (c:(Parameters:(0:UID)) != "")(
			if (c:(Parameters:(0:UID)) == c:(Parameters:(1:UID)))(
				c:Flags |= Flag:_Skip_
			)
		)
	)
)