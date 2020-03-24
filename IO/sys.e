type system,

system sys,
system Info,

system Source_File,
system Destination_File,
system OS,
system Architecture,
system Obj_Type,
system Bits_Mode,

$if (sys:(Info:OS) == "win32")(
	using "win32.e"
)

$if (sys:(Info:OS) == "unix")(
	using "unix.e"
)

system Lexer,
system Parser,
system Selector,

system Name,
system Flags,
ststem Offsetter,
system Right_Side,
system Left_Side,
system Childs,

system _Number_,
system _External_,
system _Type_,
system _Function_,
system _Array_,
system _Condition_,
system _Operator_,
system _Returning_,
system _Call_,
system _Parameter_,
system _Parenthesis_,
system _Constructor_,
system _Register_,
system _Inheritting_,
system Task_For_Returning,
system Task_For_Type_Address_Basing,
system Task_For_Type_Address,
system Task_For_Moving_Parameter,
system Task_For_Offsetting,
system Task_For_Remainder,
system Task_For_General_Purpose,
system Task_For_Floating_Math,
system _Need_For_Space_,
system _Generated_,
system _Pointting_,
system _Array_,
system _Giving_Address_,
system _String_,