#Boost variables:

type _STRING_
type _IR_
type _TOKEN_
type _LIST_
type _INTEGER_
_INTEGER_ _FLAG_
_INTEGER_ _STACK_OFFSET_
_STRING_ _UID_
_STRING_ _COMMENT_

_LIST_ _INPUT_
_INTEGER_ _PREVIOUS_
_INTEGER_ _CURRENT_
_INTEGER_ _NEXT_


_IR_ _ID_
_LIST_ _PARAMETERS_

_TOKEN_ _FLAGS_
_TOKEN_ _NAME_
_TOKEN_ _TYPE_
_FLAG_ _REGISTER_
_FLAG_ _NUMBER_
_FLAG_ _EXTERNAL_
_FLAG_ _TYPE_
_FLAG_ _FUNCTION_
_FLAG_ _ARRAY_
_FLAG_ _CONDITION_
_FLAG_ _OPERATOR_
_FLAG_ _RETURNING_
_FLAG_ _CALL_
_FLAG_ _PARAMETER_
_FLAG_ _PARANTHESIS_
_FLAG_ _CONSTRUCTOR_
_FLAG_ _REGISTER_

_FLAG_ _TASK_FOR_NON_VOLATILING_
_FLAG_ _TASK_FOR_RETURNING_
_FLAG_ _TASK_FOR_STACK_BASE_ADDRESSING_
_FLAG_ _TASK_FOR_STACK_ADDRESSING_
_FLAG_ _TASK_FOR_DEST_OFFSETTING_
_FLAG_ _TASK_FOR_SOURCE_OFFSETTING_
_FLAG_ _TASK_FOR_REMAINDER_
_FLAG_ _TASK_FOR_GENERAL_PURPOSE_
_FLAG_ _TASK_FOR_FLOATING_MATH_

_FLAG_ _NEED_FOR_SPACE_
_FLAG_ _GENERATED_

_FLAG_ _POINTTING_
_FLAG_ _ARRAY_
_FLAG_ _GIVING_ADDRESS_
_FLAG_ _STRING_
_FLAG_ _PREPROSESSOR_
_FLAG_ _SKIP_


#this pattern moves the number straight into the memory address
$pattern (
	if (_CURRENT_:_ID_ == "ldr")(
		if (_NEXT_:_ID_ == "=")(
			if (_CURRENT_:(_PARAMETERS_:(0:_FLAGS_)) & _FLAG_:_REGISTER_)(
				if (_CURRENT_:(_PARAMETERS_:(1:_FLAGS_)) & _FLAG_:_NUMBER_)(
					if (_NEXT_:(_PARAMETERS_:(0:_FLAGS_)) !& _FLAG_:_REGISTER_)(
						if (_NEXT_:(_PARAMETERS_:(1:_FLAGS_)) & _FLAG_:_REGISTER_)(
							_CURRENT_:_FLAGS_ |= _FLAG_:_SKIP_,
							_NEXT_:(_PARAMETERS_:1) = _CURRENT_:(_PARAMETERS_:1)
						)
					)
				)
			)
		)
	)
)

#This pattern checks if we can make "reg <- 0" into just "xor reg, reg".
$pattern (
	if (_CURRENT_:_ID_ == "ldr")(
		if (_CURRENT_:(_PARAMETERS_:(0:_FLAGS_)) & _FLAG_:_REGISTER_)(
			if (_CURRENT_:(_PARAMETERS_:(1:_NAME_)) == "0")(
				_CURRENT_:(_PARAMETERS_:1) = _CURRENT_:(_PARAMETERS_:0),
				_CURRENT_:_ID_ = "^"
			)
		)
	)
)

#this pattern deletes reduntant savind/loading issues.
$pattern(
	if (_CURRENT_:_ID_ == "=")(
		if (_NEXT_:_ID_ == "ldr")(
			if (_CURRENT_:(_PARAMETERS_:(0:_NAME_)) == _NEXT_:(_PARAMETERS_:(1:_NAME_)))(
				if (_CURRENT_:(_PARAMETERS_:(1:_UID_)) == _NEXT_:(_PARAMETERS_:(0:_UID_)))(
					_CURRENT_:_FLAGS_ |= _FLAG_:_SKIP_,
					_NEXT_:_FLAGS_ |= _FLAG_:_SKIP_,
				)
			)
		)
	)
)

#this pattern deletes moving same reg into same reg.
$pattern(
	if (_CURRENT_:_ID_ == "ldr")(
		if (_CURRENT_:(_PARAMETERS_:(0:_UID_)) != "")(
			if (_CURRENT_:(_PARAMETERS_:(0:_UID_)) == _CURRENT_:(_PARAMETERS_:(1:_UID_)))(
				_CURRENT_:_FLAGS_ |= _FLAG_:_SKIP_
			)
		)
	)
	if (_CURRENT_:_ID_ == "=")(
		if (_CURRENT_:(_PARAMETERS_:(0:_UID_)) != "")(
			if (_CURRENT_:(_PARAMETERS_:(0:_UID_)) == _CURRENT_:(_PARAMETERS_:(1:_UID_)))(
				_CURRENT_:_FLAGS_ |= _FLAG_:_SKIP_
			)
		)
	)
)
 

#this pattern deletes reduntant loading of mem into two different regs
$pattern (
	if (_PREVIOUS_:_ID_ == "ldr")(
		if (_CURRENT_:_ID_ == "ldr")(
			if (_PREVIOUS_:(_PARAMETERS_:(1:_NAME_)) == _CURRENT_:(_PARAMETERS_:(1:_NAME_)))(
				if (_NEXT_:_FLAGS_ & _FLAG_:_OPERATOR_)(
					if (_NEXT_:(_PARAMETERS_:(0:_UID_)) == _PREVIOUS_:(_PARAMETERS_:(0:_UID_)))(
						if (_NEXT_:(_PARAMETERS_:(1:_UID_)) == _CURRENT_:(_PARAMETERS_:(0:_UID_)))(
							_CURRENT_:_FLAGS_ |= _FLAG_:_SKIP_,
							_NEXT_:(_PARAMETERS_:1) = _PREVIOUS_:(_PARAMETERS_:0),
							_NEXT_:_COMMENT_ ="Boosted"
						)
					)
				)
			)
		)
	)
)

#this pattern deletes reuse of same opcode
#by chekking the previus to have the same code as next 
#but current doesnt change eny of them then skip the
#example:
#mov ecx, ebx
#mov ....
#mov ecx, ebx

$pattern (
	if (_PREVIOUS_:_ID_ == "ldr")(
		if (_PREVIOUS_:_ID_ == _NEXT_:_ID_)(
			if (_PREVIOUS_:(_PARAMETERS_:(0:_NAME_)) == _NEXT_:(_PARAMETERS_:(0:_NAME_)))(
				if (_PREVIOUS_:(_PARAMETERS_:(1:_NAME_)) == _NEXT_:(_PARAMETERS_:(1:_NAME_)))(
					if (_CURRENT_:(_PARAMETERS_:(0:_NAME_)) == _PREVIOUS_:(_PARAMETERS_:(0:_NAME_)))(
						if (_CURRENT_:(_PARAMETERS_:(0:_FLAGS_)) & _FLAG_:_POINTTING_)(
							_NEXT_:_FLAGS_ |= _FLAG_:_SKIP_
						)
						if (_CURRENT_:(_PARAMETERS_:(0:_FLAGS_)) & _FLAG_:_ARRAY_)(
							_NEXT_:_FLAGS_ |= _FLAG_:_SKIP_
						)
					)
					if (_CURRENT_:(_PARAMETERS_:(0:_NAME_)) != _PREVIOUS_:(_PARAMETERS_:(0:_NAME_)))(
						_NEXT_:_FLAGS_ |= _FLAG_:_SKIP_
					)
				)
			)
		)
	)
)