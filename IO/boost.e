#Boost variables:

type String,
type IR,
type Token,
type List,
type Integer,
Integer Flag,
Integer Stack_Offset,
String UID,
String Comment,

List IN,
Integer _p,
Integer _c,
Integer _n,


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


#this pattern moves the number straight into the memory address
$pattern (
	if (_c:ID == "ldr")(
		if (_n:ID == "=")(
			if (_c:(Parameters:(0:Flags)) & Flag:_Register_)(
				if (_c:(Parameters:(1:Flags)) & Flag:_Number_)(
					if (_n:(Parameters:(0:Flags)) !& Flag:_Register_)(
						if (_n:(Parameters:(1:Flags)) & Flag:_Register_)(
							_c:Flags |= Flag:_Skip_,
							_n:(Parameters:1) = _c:(Parameters:1)
						)
					)
				)
			)
		)
	)
)

#This pattern checks if we can make "reg <- 0" into just "xor reg, reg".
$pattern (
	if (_c:ID == "ldr")(
		if (_c:(Parameters:(0:Flags)) & Flag:_Register_)(
			if (_c:(Parameters:(1:Name)) == "0")(
				_c:(Parameters:1) = _c:(Parameters:0),
				_c:ID = "^"
			)
		)
	)
)

#this pattern deletes reduntant savind/loading issues.
$pattern(
	if (_c:ID == "=")(
		if (_n:ID == "ldr")(
			if (_c:(Parameters:(0:Name)) == _n:(Parameters:(1:Name)))(
				if (_c:(Parameters:(1:UID)) == _n:(Parameters:(0:UID)))(
					_c:Flags |= Flag:_Skip_,
					_n:Flags |= Flag:_Skip_,
				)
			)
		)
	)
)

#this pattern deletes moving same reg into same reg.
$pattern(
	if (_c:ID == "ldr")(
		if (_c:(Parameters:(0:UID)) != "")(
			if (_c:(Parameters:(0:UID)) == _c:(Parameters:(1:UID)))(
				_c:Flags |= Flag:_Skip_
			)
		)
	)
	if (_c:ID == "=")(
		if (_c:(Parameters:(0:UID)) != "")(
			if (_c:(Parameters:(0:UID)) == _c:(Parameters:(1:UID)))(
				_c:Flags |= Flag:_Skip_
			)
		)
	)
)
 

#this pattern deletes reduntant loading of mem into two different regs
$pattern (
	if (_p:ID == "ldr")(
		if (_c:ID == "ldr")(
			if (_p:(Parameters:(1:Name)) == _c:(Parameters:(1:Name)))(
				if (_n:Flags & Flag:_Operator_)(
					if (_n:(Parameters:(0:UID)) == _p:(Parameters:(0:UID)))(
						if (_n:(Parameters:(1:UID)) == _c:(Parameters:(0:UID)))(
							_c:Flags |= Flag:_Skip_,
							_n:(Parameters:1) = _p:(Parameters:0),
							_n:Comment = "Boosted"
						)
					)
				)
			)
		)
	)
)