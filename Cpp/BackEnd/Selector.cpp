#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Usr.h"
#include "../../H/UI/Safe.h"

extern Usr* sys;
extern x86_64_Win X86_64_WIN;
extern ARM_64 _ARM_64;

void Selector::Init() {
	if (sys->Info.Architecture == "x86") {
		if (sys->Info.Bits_Mode == "8") {
			if (sys->Info.OS == "win") {
				X86_64_WIN.Init();
				for (auto i : X86_64_WIN.Registers)
					Registers.push_back({ nullptr, i });
				for (auto i : X86_64_WIN.Parameter_Registers) {
					Parameter_Registers.push_back(Transform(i));
				}
				Opcodes = X86_64_WIN.Opcodes;
				Size_Identifiers = X86_64_WIN.Size_Identifiers;

				//DEBUG
				STACK_REPRESENTIVE_REGISTER = X86_64_WIN.STACK_REPRESENTIVE_REGISTER;
			}
		}

	}
	else if (sys->Info.Architecture == "arm") {
		if (sys->Info.Bits_Mode == "8") {
			if (sys->Info.OS == "win" || sys->Info.OS == "unix") {
				_ARM_64.Init();
				for (auto i : _ARM_64.Registers)
					Registers.push_back({ nullptr, i });
				for (auto i : _ARM_64.Parameter_Registers) {
					Parameter_Registers.push_back(Transform(i));
				}
				Opcodes = _ARM_64.Opcodes;
				Size_Identifiers = _ARM_64.Size_Identifiers;

				//DEBUG
				STACK_REPRESENTIVE_REGISTER = X86_64_WIN.STACK_REPRESENTIVE_REGISTER;
			}
		}
	}
}

bool Selector::Find(string n, Token* ast)
{
	if (ast->Get_Name() == n)
		return true;
	if (ast->is(TOKEN::CONTENT) || ast->is(TOKEN::MEMORY))
		for (auto& i : ast->Childs)
			//throw::runtime_error("haha nobnob");
			return Find(n, i);
	if (ast->is(TOKEN::OFFSETTER) || ast->is(TOKEN::DEOFFSETTER) || ast->is(TOKEN::SCALER)) {
		if (Find(n, ast->Left))
			return true;
		if (Find(n, ast->Right))
			return true;
	}
	return false;
}

bool Selector::Find(Token* n, Token* ast)
{
	if (ast->Get_Name() == n->Get_Name() && ast->is(n->Get_Flags()))
		return true;
	if (ast->is(TOKEN::CONTENT) || ast->is(TOKEN::MEMORY))
		for (auto& i : ast->Childs)
			//throw::runtime_error("haha nobnob");
			return Find(n, i);
	if (ast->is(TOKEN::OFFSETTER) || ast->is(TOKEN::DEOFFSETTER) || ast->is(TOKEN::SCALER)) {
		if (Find(n, ast->Left))
			return true;
		if (Find(n, ast->Right))
			return true;
	}
	return false;
}

int L1 = 0;
vector<Token*> Selector::Transform(Token* parent)
{
	vector<Token*> Result;
	if (L1 == 0)
		Result.push_back(parent);
	L1++;
	for (auto c : *parent->Get_Childs()) {
		Result.push_back(c);
		vector<Token*> r = Transform(c);
		Result.insert(Result.end(), r.begin(), r.end());
	}
	L1--;
	return Result;
}

Path* Selector::Get_Path_Info(vector<IR*> source, int i, Token* t) {
	Path* p = new Path;
	//try to find if this t* is used in future
	//also check if it intersects cllations
	vector<int> Intersects_Calls;
	int Crossed_Call = -1;
	int Parameter_Place = -1;
	int Last_Usage = i;
	for (int j = i; j < source.size(); j++) {
		for (auto k : source[j]->Arguments) {
			//TODO: Cheking names wont work on duplicated local varibles inside a condition like scopes.
			if (Find(t, k)) {
				//check if this is the same variable...
				Last_Usage = j;
				if (Crossed_Call != -1) {
					Intersects_Calls.push_back(Crossed_Call);
					Crossed_Call = -1;
				}
			}
		}
		if (source[j]->is(TOKEN::CALL)) {
			Crossed_Call = j;
			//Intersects_Calls.push_back(j);
			for (int k = 0; k < source[j]->OPCODE->Parameters.size(); k++)
				if (source[j]->OPCODE->Parameters[k]->Get_Name() == t->Get_Name()) {
					Last_Usage = j;
					Parameter_Place = k;
				}
		}
		if (source[j]->is(TOKEN::END_OF_FUNCTION))
			break;
	}
	p->Intersects_Calls = Intersects_Calls;
	p->Last_Usage = Last_Usage;
	p->Parameter_Place = Parameter_Place;
	return p;
}

void Selector::Make_Solution_For_Crossed_Register_Usages(pair<Register_Descriptor*, Token*> Current, pair<Register_Descriptor*, Token*> New, vector<IR*>* source, int i)
{
	/*
	mov rbx, [a]
	;try to find non-volatile
	;if no non_volatile then use stack
	;inform stack about the new push
	add rbx, [c]	//a += c
	mov rcx, [b]
	call banana(b)
	mov rcx, rbx
	call banana(a)
	*/
	//get a new non-volatile register to use
	Token* non_volatile = Get_Register(TOKEN::NONVOLATILE, New.first, i, New.second);
	string non_Name = non_volatile->Get_Name();
	string Current_Name = Current.second->Get_Name();
	if (non_volatile == nullptr) {
		//if this happends then all registers are in use and we need to use stack
	}
	else {
		non_volatile = new Token(non_volatile->Get_Flags(), "Non-Volatile" + to_string(rand()), non_volatile->Get_Size());
		non_volatile->ID = non_Name;
	}
	Token* Current_Reg = new Token(Current.second->Get_Flags(), "Current_Volatile" + to_string(rand()), Current.second->Get_Size());
	Current_Reg->ID = Current_Name;
	//now we need to give the cuurent user the new non-volatile register.
	//TODO: Because im a peace of shit and dont know how to implement LIVE register change ill have to make a new move IR
	IR* MOV = new IR(new Token(TOKEN::OPERATOR, "="), {non_volatile, Current_Reg }, nullptr);

	//insert the mov before the new user starts
	source->insert(source->begin() + New.first->First_Usage_Index, MOV);

	//the load back is handled by the situation system, call, etc..

	//now we need to give the current user the new non-volatile
	//if the non-volatile area is a memory then no need to pair
	if (!non_volatile->is(TOKEN::MEMORY))
		Pair_Up(non_volatile, Current.first);

	//break the old connection between the register and the user
	Break_Up(Current.second);

	Pair_Up(Current.second, New.first);
}

Token* Selector::Move_Parameter_Into_Non_Volatile(pair<Path*, Token*> Owner, Token* Current_Reg, vector<IR*>* source, int i)
{
	Token* New_Reg = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, Owner.second->Get_Name(), Owner.second->Get_Size());
	New_Reg->ID = Get_New_Reg(source, i, New_Reg, Owner.first)->Get_Name();

	Token* New_Token = new Token(*Owner.second);

	New_Token->ID = Current_Reg->Get_Name();
	//New_Token->Set_Name(Current_Reg->Get_Name());

	source->insert(source->begin() + i, new IR(new Token(TOKEN::OPERATOR, "="), { New_Reg, New_Token }, nullptr));

	return New_Reg;
}

Token* Selector::Get_New_Reg(vector<IR*>* source, int i, Token* t, Path* path)
{
	Path* p = path;
	if (p == nullptr)
		p = Get_Path_Info(*source, i, t);
	if (p->Parameter_Place != -1 && (p->Parameter_Place <= Parameter_Registers.size())) {
		//TODO: this can go broke if there is one or more calls before this so the parameter chosen by this is going to be overwritten :(
		Token* reg = Get_Right_Parameter_Register(t, p->Parameter_Place);

		for (auto& r : Registers) {
			if (r.second->Get_Name() != reg->Get_Name())
				//skip until we get into the right register
				continue;
			if (r.first == nullptr || r.first->Last_Usage_Index <= p->Last_Usage) {
				//no current owner
				r.first = new Register_Descriptor(i, p->Last_Usage, t->Get_Name());
				return r.second;
			}
			else if (r.first->Last_Usage_Index > p->Last_Usage){
				//if the current register user is more superior register user than us, then we need to do a temporary save to stack 
				Make_Solution_For_Crossed_Register_Usages({ r.first, r.second }, { new Register_Descriptor(i, p->Last_Usage, t->Get_Name()), t }, source, i);
				//now the wanted register is solutioned :D
				return r.second;
			}
		}
	}
	long long Reg_Type = 0;
	if (t->is(TOKEN::RETURNING))
		Reg_Type |= TOKEN::RETURNING;
	else if (t->is(TOKEN::REMAINDER))
		Reg_Type |= TOKEN::REMAINDER;
	else if (t->is(TOKEN::QUOTIENT))
		Reg_Type |= TOKEN::QUOTIENT;
	else if (t->is(TOKEN::PARAMETER))
		Reg_Type |= TOKEN::PARAMETER;
	else if (t->is(TOKEN::STACK_POINTTER))
		Reg_Type |= TOKEN::STACK_POINTTER;
	else if (t->is(TOKEN::POSITION_INDEPENDENT_REGISTER))
		Reg_Type |= TOKEN::POSITION_INDEPENDENT_REGISTER;
	else if ((p->Intersects_Calls.size() > 0))
		Reg_Type |= TOKEN::NONVOLATILE;
	else if (t->is(TOKEN::NONVOLATILE))
		Reg_Type |= TOKEN::NONVOLATILE;
	else
		Reg_Type |= TOKEN::VOLATILE;
	if (t->is(TOKEN::DECIMAL))
		Reg_Type |= TOKEN::DECIMAL;
	//because there is usually only one register for those purposes we need to enable same typed register usage
	//example: mov eax, eax, if we are returning a call value the value resides in a eax, and the return value in eax.
	//optimizer will remove these errors later on.
	bool Single_Register_Type = t->is(TOKEN::RETURNING) || t->is(TOKEN::REMAINDER) || t->is(TOKEN::QUOTIENT) || t->is(TOKEN::STACK_POINTTER) || t->is(TOKEN::POSITION_INDEPENDENT_REGISTER);

	if (t->Parameter_Index != -1) {
		Token* reg = nullptr;
		int Type_Offset = 0;
		if (t->is(TOKEN::DECIMAL)) {
			while (!Parameter_Registers[Type_Offset][0]->is(TOKEN::DECIMAL))
				Type_Offset++;
		}
		for (auto k : Parameter_Registers[(size_t)Type_Offset + t->Parameter_Index])
			if (k->Get_Size() == t->Get_Size()) {
				reg = k;
				break;
			}

		for (auto& r : Registers) {
			if (r.second->Get_Name() == reg->Get_Name()) {
				if (r.first == nullptr || r.first->Last_Usage_Index <= p->Last_Usage) {

					if (p->Intersects_Calls.size() > 0)
						return Move_Parameter_Into_Non_Volatile({ p, t }, r.second, source, i);

					r.first = new Register_Descriptor(i, p->Last_Usage, t->Get_Name());

					return r.second;
				}
				else if (r.first->User == t->Get_Name()) {
					return r.second;
				}
				else if (r.first->Last_Usage_Index > p->Last_Usage) {
					//if the current register user is more superior register user than us, then we need to do a temporary save to stack 
					Make_Solution_For_Crossed_Register_Usages({ r.first, r.second }, { new Register_Descriptor(i, p->Last_Usage, t->Get_Name()), t }, source, i);
					//now the wanted register is solutioned :D
					return r.second;
				}
				else {
					return nullptr;
				}
			}
		}
	}

	//for (auto j : p->Intersects_Calls) {
	//	for (auto a : source->at(j)->OPCODE->Parameters) {
	//		Get_New_Reg(source, j, a);
	//	}
	//}

	for (auto& r : Registers) {
		if (r.second->is(TOKEN::DECIMAL))
			if (!t->is(TOKEN::DECIMAL))
				continue;
		if (r.first == nullptr) {
			if (r.second->is(Reg_Type)) {
				for (auto s : *r.second->Get_Childs())
					if (Check_If_Smaller_Register_Is_In_Use(s) != nullptr)
						if (Check_If_Smaller_Register_Is_In_Use(s)->Last_Usage_Index > i)
							goto Wrong;
				if (r.second->Holder != nullptr)
					if (Check_If_Larger_Register_Is_In_Use(r.second->Holder) != nullptr)
						if (Check_If_Larger_Register_Is_In_Use(r.second->Holder)->Last_Usage_Index > i)
							goto Wrong;
				if (r.second->Get_Size() == t->Get_Size()) {
					r.first = new Register_Descriptor(i, p->Last_Usage, t->Get_Name());
					return r.second;
				}
			}
		}
		//									no need because the arguments are now reversed!
		//								   <= is wrong because the old user doesnt find the register it belong into.
		else if (r.first->Last_Usage_Index <= i && r.second->is(Reg_Type) && r.second->Get_Size() == t->Get_Size()) {
			for (auto s : *r.second->Get_Childs())
				if (Check_If_Smaller_Register_Is_In_Use(s) != nullptr)
					if (Check_If_Smaller_Register_Is_In_Use(s)->Last_Usage_Index > i)
						goto Wrong;
			if (r.second->Holder != nullptr)
				if (Check_If_Larger_Register_Is_In_Use(r.second->Holder) != nullptr)
					if (Check_If_Larger_Register_Is_In_Use(r.second->Holder)->Last_Usage_Index > i)
						goto Wrong;
			r.first->Last_Usage_Index = p->Last_Usage;
			r.first->User = t->Get_Name();
			return r.second;
		}
		else if (Single_Register_Type && r.second->is(Reg_Type) && r.second->Get_Size() == t->Get_Size()) {
			Make_Solution_For_Crossed_Register_Usages({ r.first, r.second }, { new Register_Descriptor(i, p->Last_Usage, t->Get_Name()), t }, source, i);
			return r.second;
		}
		//still... checking names is wrong
		else if (r.first->User == t->Get_Name()) {
			return r.second;
		}
	Wrong:;
	}
	//if the code gets here, then return nullptr to indicate that we need to release some registers
	return nullptr;
}

Token* Selector::Get_Right_Parameter_Register(Token* t, int parameter_index)
{
	int Offset = 0;
	if (t->is(TOKEN::DECIMAL))
		for (auto i : Parameter_Registers) {
			if (i[0]->is(TOKEN::DECIMAL))
				break;
			Offset++;
		}

	if (sys->Info.OS == "win") {
		int Location = (size_t)Offset + parameter_index;
		if (t->is(TOKEN::DECIMAL) && !Previus_Parameter_Type_Decimal)
			Location += Current_Parameter_Register_Index;
		else if (!t->is(TOKEN::DECIMAL) && Previus_Parameter_Type_Decimal)
			Location += Current_Parameter_Register_Index;

		for (auto& k : Parameter_Registers[Location])
			if (k->Get_Size() == t->Get_Size()) {
				Current_Parameter_Register_Index++;
				if (t->is(TOKEN::DECIMAL))
					Previus_Parameter_Type_Decimal = true;
				else
					Previus_Parameter_Type_Decimal = false;
				return k;
			}
	}
	else if (sys->Info.OS == "unix") {
		for (auto& k : Parameter_Registers[(size_t)Offset + parameter_index])
			if (k->Get_Size() == t->Get_Size()) {
				return k;
			}
	}
	throw::runtime_error("ERROR!");
}

void Selector::Reset_Parameter_Register_Count(IR* r)
{
	if (!r->OPCODE->is(TOKEN::CALL))
		return;
	
	Current_Parameter_Register_Index = 0;
}

Token* Selector::Get_Register(Token* t)
{
	for (auto& i : Registers)
		if ((i.first != nullptr) && i.first->User == t->Get_Name())
			if (i.second->Get_Size() == t->Get_Size())
				return i.second;

	for (auto& i : Registers)
		if ((i.first != nullptr) && i.first->User == t->Get_Name()) {
			if (i.second->Get_Size() == t->Get_Size())
				return i.second;
			else {
				if (i.second->Get_Size() < t->Get_Size()) {
					for (auto& j : Registers)
						if (i.second->Holder->Get_Name() == j.second->Get_Name()) {
							j.first = new Register_Descriptor(*i.first);
							return j.second;
						}
				}
			}
		}
	return nullptr;	//need to use Get_New_Reg();
}

Token* Selector::Get_Register(long F, Register_Descriptor* user, int i, Token* t)
{
	bool Single_Register_Type = F == TOKEN::RETURNING || F == TOKEN::REMAINDER || F == TOKEN::QUOTIENT || F == TOKEN::STACK_POINTTER;

	for (auto& r : Registers) {
		if (!r.second->is(F))
			continue;
		if (r.second->Get_Size() != t->Get_Size())
			continue;
		if (r.first == nullptr) {
			for (auto s : *r.second->Get_Childs())
				if (Check_If_Smaller_Register_Is_In_Use(s) != nullptr)
					if (Check_If_Smaller_Register_Is_In_Use(s)->Last_Usage_Index > i && !Single_Register_Type)
						goto Wrong;
			if (r.second->Holder != nullptr)
				if (Check_If_Larger_Register_Is_In_Use(r.second->Holder) != nullptr)
					if (Check_If_Larger_Register_Is_In_Use(r.second->Holder)->Last_Usage_Index > i && !Single_Register_Type)
						goto Wrong;
			r.first = user;
			return r.second;
		}
		else if (r.first->Last_Usage_Index <= i + Single_Register_Type) {
			for (auto s : *r.second->Get_Childs())
				if (Check_If_Smaller_Register_Is_In_Use(s) != nullptr)
					if (Check_If_Smaller_Register_Is_In_Use(s)->Last_Usage_Index > i && !Single_Register_Type)
						goto Wrong;
			if (r.second->Holder != nullptr)
				if (Check_If_Larger_Register_Is_In_Use(r.second->Holder) != nullptr)
					if (Check_If_Larger_Register_Is_In_Use(r.second->Holder)->Last_Usage_Index > i && !Single_Register_Type)
						goto Wrong;
			r.first = user;
			return r.second;
		}
		//still... checking names is wrong
		else if (r.first->User == t->Get_Name()) {
			return r.second;
		}
	Wrong:;
	}
	//if this gets here, all non & non-non-volatile register are used already.
	//use stack
	return nullptr;
}

int Selector::Get_Largest_Register()
{
	int Result = 0;
	for (auto i : Registers)
		if (i.second->Get_Size() > Result)
			Result = i.second->Get_Size();
	return Result;
}

Register_Descriptor* Selector::Check_If_Smaller_Register_Is_In_Use(Token* r)
{
	for (auto i : Registers) {
		if (i.second->Get_Name() == r->Get_Name()) {
			if (i.first != nullptr)
				return i.first;
			for (auto j : i.second->Childs) {
				if (Check_If_Smaller_Register_Is_In_Use(j) != nullptr)
					return Check_If_Smaller_Register_Is_In_Use(j);
			}
			return nullptr;
		}
	}
	throw::runtime_error("INTERNAL ERROR!");
}

Register_Descriptor* Selector::Check_If_Larger_Register_Is_In_Use(Token* r)
{
	for (auto i : Registers) {
		if (i.second->Get_Name() == r->Get_Name()) {
			if (i.first != nullptr)
				return i.first;
			if (r->Holder == nullptr)
				return nullptr;
			return Check_If_Larger_Register_Is_In_Use(r->Holder);
		}
	}
	throw::runtime_error("INTERNAL ERROR!");
}

void Selector::Allocate_Register(vector<IR*>* source, int i, Token* t)
{
	//move some register into a non-volatile register
	//if all the non-volatile registers are already occupied then use stack
	//we have Save/Load commads for them (:
	Path* p = Get_Path_Info(*source, i, t);
	for (auto& r : Registers) {
		if (!r.second->is(TOKEN::NONVOLATILE))
			continue;
		if (r.second->Get_Size() != t->Get_Size())
			continue;
		if (r.first == nullptr) {
			r.first = new Register_Descriptor(i, p->Last_Usage, t->Get_Name());
			return;
		}
	}
	cout << "allocation needed!" << endl;
	throw::runtime_error("INTERNAL ERROR!");
}

void Selector::Pair_Up(Token* r, Register_Descriptor* t)
{
	for (auto& i : Registers)
		if (i.second->Get_Name() == r->Get_Name() || i.second->Get_Name() == r->ID) {
			i.first = t;
			return;
		}
}

void Selector::Break_Up(Token* r)
{
	for (auto& i : Registers)
		if (i.second->Get_Name() == r->Get_Name() || i.second->Get_Name() == r->ID) {
			i.first = nullptr;
			return;
		}
}

int Selector::Get_Numerical_Parameter_Register_Count(vector<Node*> Parameters)
{
	if(sys->Info.OS == "win") {
		//first get the amount of all non decimal registers
		int Non_Decimal_Register_Count = 0;
		for (auto i : Parameter_Registers) {
			if (!i[0]->is(TOKEN::DECIMAL))
				Non_Decimal_Register_Count++;
		}
		//then get the amount of all decimal registers
		int Decimal_Register_Count = 0;
		for (auto i : Parameter_Registers) {
			if (i[0]->is(TOKEN::DECIMAL))
				Decimal_Register_Count++;
		}
		//then count the number of decimal parameters used in the Parameters list
		int Parameter_Decimal_Register_Count = 0;
		for (auto i : Parameters) {
			if (i->is(TOKEN::DECIMAL))
				Parameter_Decimal_Register_Count++;
		}
		//now that we have the amount of possible decimal register count and the used amount of them we can
		//calculate the substraction of the used decimal registers from non decimal registers, bear with me.
		return Non_Decimal_Register_Count - (Decimal_Register_Count - (Decimal_Register_Count - Parameter_Decimal_Register_Count));
	}
	else {
		int Non_Decimal_Register_Count = 0;
		for (auto i : Parameter_Registers) {
			if (!i[0]->is(TOKEN::DECIMAL))
				Non_Decimal_Register_Count++;
		}
		return Non_Decimal_Register_Count;
	}
}

int Selector::Get_Floating_Parameter_Register_Count(vector<Node*> Parameters)
{
	if (sys->Info.OS == "win") {
		//first get the amount of all non decimal registers
		int Non_Decimal_Register_Count = 0;
		for (auto i : Parameter_Registers) {
			if (!i[0]->is(TOKEN::DECIMAL))
				Non_Decimal_Register_Count++;
		}
		//then get the amount of all decimal registers
		int Decimal_Register_Count = 0;
		for (auto i : Parameter_Registers) {
			if (i[0]->is(TOKEN::DECIMAL))
				Decimal_Register_Count++;
		}
		//then count the number of non decimal parameters used in the Parameters list
		int Parameter_Non_Decimal_Register_Count = 0;
		for (auto i : Parameters) {
			if (!i->is(TOKEN::DECIMAL))
				Parameter_Non_Decimal_Register_Count++;
		}
		//now that we have the amount of possible non decimal register count and the used amount of them, we can
		//calculate the substraction of the used non decimal registers from decimal registers, bear with me.
		return Decimal_Register_Count - (Non_Decimal_Register_Count - (Non_Decimal_Register_Count - Parameter_Non_Decimal_Register_Count));
	}
	else {
		int Decimal_Register_Count = 0;
		for (auto i : Parameter_Registers) {
			if (i[0]->is(TOKEN::DECIMAL))
				Decimal_Register_Count++;
		}
		return Decimal_Register_Count;
	}
}

void Selector::Clean_Register_Holders()
{
	for (auto& r : Registers) {
		r.first = nullptr;
	}
}

vector<pair<Register_Descriptor*, Token*>> Selector::Get_Register_Type(long f)
{
	vector<pair<Register_Descriptor*, Token*>> Result;
	for (auto& i : Registers) {
		if (i.second->is(f))
			Result.push_back(i);
	}
	return Result;
}

void Selector::DeAllocate_Stack(int Amount, vector<IR*>* list, int i)
{
	//add rsp, 123 * 16
	//if used call in scope use stack.size() % 16 = 0;
	list->insert(list->begin() + i, new IR(new Token(TOKEN::OPERATOR, "+"), { new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK",  _SYSTEM_BIT_SIZE_), new Token(TOKEN::NUM, to_string(Amount), _SYSTEM_BIT_SIZE_) }, nullptr));
}

void Selector::Allocate_Stack(int Amount, vector<IR*>* list, int i)
{
	//sub rsp, 123 * 16
	//if used call in scope use stack.size() % 16 = 0;
	list->insert(list->begin() + i, new IR(new Token(TOKEN::OPERATOR, "-"), { new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK", _SYSTEM_BIT_SIZE_), new Token(TOKEN::NUM, to_string(Amount), _SYSTEM_BIT_SIZE_) }, nullptr));
}

int Selector::Update_Stack_Size()
{
	//go through the stack variables, then return sum.
	Stack_Size = 0;
	for (auto i : Stack)
		Stack_Size += i->Get_Size();
	return Stack_Size + Start_Offset;
}

void Selector::Clean_Stack()
{
	Stack.clear();
	Start_Offset = 0;
}

IR* Selector::Get_Opcode(IR* i)
{
	vector<int> sizes;
	//this gives the selector information about the sizes of these arguments
	for (auto s : i->Arguments)
		sizes.push_back(s->Get_Size());

	for (auto opc : Opcodes) {
		if (opc->ID != i->OPCODE->Get_Name())
			continue;
		for (auto o : opc->Order) {
			//check if this order has same amount of arguments as i.
			if (o.size() != sizes.size())
				continue;	//this is wrong order
			for (int j = 0; j < sizes.size(); j++) {
				if (!(o[j].second.first <= sizes[j] && o[j].second.second >= sizes[j]))
					goto Wrong;
			}
			//if (!Check_Resource_Availability(i, o))
			//	goto Wrong;
			for (int j = 0; j < sizes.size(); j++) {
				if (!o[j].first->is(i->Arguments[j]->Get_Flags()))
					goto Wrong;
			}
			return opc;
		Wrong:;
		}
		if (opc->Order.size() < 1) {
			if (sizes.size() == 0)
				return opc;
		}
	}
	string args = "(";
	for (auto j : i->Arguments)
		args += j->Get_Name() + "[" + to_string(j->Get_Size()) + "]" + ", ";
	args += ")";
	Report(Observation(ERROR, "No suitable OPCODE found for " + i->OPCODE->Get_Name() + args, Position()));
	throw std::runtime_error("Error");
	return nullptr;
}

bool Selector::Check_Resource_Availability(IR* opc, vector<pair<Token*, pair<int, int>>> Order)
{
	int Register_Usage = 0;
	int Const_Usage = 0;
	int Scaler_Usage = 0;
	for (auto& i : opc->Arguments) {

	}
	return false;
}

string Selector::Get_Size_Identifier(int s)
{
	for (auto i : Size_Identifiers) {
		if (i->Get_Size() == s)
			return i->Get_Name();
	}
	Report(Observation(ERROR, "Size identifier for size of '" + to_string(s) + "' wasnt found!", Position()));
	throw::runtime_error("Error!");
}

