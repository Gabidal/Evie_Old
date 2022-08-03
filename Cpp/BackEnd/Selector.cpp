#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Usr.h"
#include "../../H/UI/Safe.h"

extern Usr* sys;
extern x86_64 X86_64;
extern ARM_64 _ARM_64;

void Selector::Init() {
	if (sys->Info.Architecture == "x86") {
		if (sys->Info.Bytes_Mode == "8") {
			X86_64.Init();
			for (auto i : X86_64.Registers)
				Registers.push_back({ nullptr, i });
			for (auto i : X86_64.Parameter_Registers) {
				Parameter_Registers.push_back(Transform(i));
			}
			Opcodes = X86_64.Opcodes;
			Size_Identifiers = X86_64.Size_Identifiers;

			//DEBUG
			STACK_REPRESENTIVE_REGISTER = X86_64.STACK_REPRESENTIVE_REGISTER;

			//Assembler
			Build = X86_64.Build;
			Assemble = X86_64.Assemble;

			//Linker
			OBJ_Machine_ID = X86_64.OBJ_Machine_ID;
		}

	}
	else if (sys->Info.Architecture == "arm") {
		if (sys->Info.Bytes_Mode == "8") {
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
				STACK_REPRESENTIVE_REGISTER = X86_64.STACK_REPRESENTIVE_REGISTER;
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
	if ((ast == n) || (ast->Get_Name() == n->Get_Name() && ast->is(n->Get_Flags())))
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

void Selector::Make_Solution_For_Crossed_Register_Usages(pair<Descriptor*, Token*> Current, pair<Descriptor*, Token*> New, vector<IR*>* source, int i)
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

	if (non_volatile == nullptr) {
		//if this happends then all registers are in use and we need to use stack
	}
	else {
		non_volatile = new Token(non_volatile->Get_Flags(), "Non-Volatile" + to_string(rand()), non_volatile->Get_Size());
		non_volatile->ID = non_volatile;
	}
	Token* Current_Reg = new Token(Current.second->Get_Flags(), "Current_Volatile" + to_string(rand()), Current.second->Get_Size());
	Current_Reg->ID = Current.second;
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
	New_Reg->ID = Get_New_Reg(source, i, New_Reg, Owner.first);

	Token* New_Token = new Token(*Owner.second);

	New_Token->ID = Current_Reg;
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
				r.first = new Descriptor(i, p->Last_Usage, t->Get_Name(), t->Get_Parent());
				return r.second;
			}
			else if (r.first->Last_Usage_Index > p->Last_Usage){
				//if the current register user is more superior register user than us, then we need to do a temporary save to stack 
				Make_Solution_For_Crossed_Register_Usages({ r.first, r.second }, { new Descriptor(i, p->Last_Usage, t->Get_Name(), t->Get_Parent()), t }, source, i);
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

					r.first = new Descriptor(i, p->Last_Usage, t->Get_Name(), t->Get_Parent());

					return r.second;
				}
				else if (r.first->User == t->Get_Name()) {
					return r.second;
				}
				else if (r.first->Last_Usage_Index > p->Last_Usage) {
					//if the current register user is more superior register user than us, then we need to do a temporary save to stack 
					Make_Solution_For_Crossed_Register_Usages({ r.first, r.second }, { new Descriptor(i, p->Last_Usage, t->Get_Name(), t->Get_Parent()), t }, source, i);
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
					r.first = new Descriptor(i, p->Last_Usage, t->Get_Name(), t->Get_Parent());
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
			Make_Solution_For_Crossed_Register_Usages({ r.first, r.second }, { new Descriptor(i, p->Last_Usage, t->Get_Name(), t->Get_Parent()), t }, source, i);
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
		for (auto& i : Parameter_Registers) {
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
			else if (i.second->Get_Size() < t->Get_Size()) {
				Token* Larger_Register = Get_Larger_Register(i.second, t);
				for (auto& j : Registers)
					if (Larger_Register->Get_Name() == j.second->Get_Name()) {
						j.first = new Descriptor(*i.first);
						return j.second;
					}
			}
			else {
				Token* Smaller_Register = Get_Smaller_Register(i.second, t);
				for (auto& j : Registers)
					if (Smaller_Register->Get_Name() == j.second->Get_Name()) {
						j.first = new Descriptor(*i.first);
						return j.second;
					}
			}
		}
	return nullptr;	//need to use Get_New_Reg();
}

Token* Selector::Get_Register(long F, Descriptor* user, int i, Token* t)
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

int Selector::Get_Largest_Register_Size()
{
	int Result = 0;
	for (auto& i : Registers)
		if (i.second->Get_Size() > Result)
			Result = i.second->Get_Size();
	return Result;
}

Descriptor* Selector::Check_If_Smaller_Register_Is_In_Use(Token* r)
{
	for (auto& i : Registers) {
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

Descriptor* Selector::Check_If_Larger_Register_Is_In_Use(Token* r)
{
	for (auto& i : Registers) {
		//if (i.second->Get_Name() == r->Get_Name()) {
		if (i.second == r){
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
		
		//get the register owner
		pair<Descriptor*, Token*>* Previus_User = Get_Register_User(Get_Largest_Register(r.second));
		
		if (Previus_User == nullptr)
			Report(Observation(ERROR, "INTERNAL PROBLEM HAS OCCURED!!", Position()));

		bool Used_Previus_Stack_Space = false;

		long long Memory_Type = 0;
		if (t->is(TOKEN::DECIMAL))
			Memory_Type = TOKEN::DECIMAL;

		Token* Memory_Location;

		//check if there is some free space already allocated from previus allocations.
		for (auto &j : Stack) {
			if (j.second->is(TOKEN::REGISTER_SAVE_SPACE) && j.first->Last_Usage_Index < i && j.second->Get_Size() == Previus_User->second->Get_Size()) {
				*j.first = *Previus_User->first;

				j.second->Set_Name(Previus_User->first->User);
				j.second->Childs.back()->Set_Name(Previus_User->first->User);
				j.second->Childs.back()->Set_Parent(t->Get_Parent());

				j.second->Set_Flags(TOKEN::MEMORY | Memory_Type);

				j.second->Set_Parent(Previus_User->first->Scope);

				Previus_User->first = nullptr;
				Used_Previus_Stack_Space = true;

				Memory_Location = j.second;
			}
		}

		if (!Used_Previus_Stack_Space) {
			//we need to allocate some space for this NONVOLATILE previus owner.
			Stack.push_back({ Previus_User->first, new Token(TOKEN::MEMORY | Memory_Type, { new Token(TOKEN::CONTENT | TOKEN::REGISTER_SAVE_SPACE, t->Get_Name(), t->Get_Size())}, t->Get_Size(), t->Get_Name()) });


			Stack.back().second->Childs.back()->Set_Parent(t->Get_Parent());

			Previus_User->first = nullptr;

			Memory_Location = Stack.back().second;
		}

		Token* New_Reg = new Token(*Previus_User->second);
		New_Reg->ID = Previus_User->second;
		New_Reg->Set_Flags(New_Reg->Get_Flags() | TOKEN::ALREADY_GIVEN_REGISTER_NAME);
		//make a move operator here:
		source->insert(source->begin() + i, new IR(new Token(TOKEN::OPERATOR, "="), {Memory_Location, New_Reg}, new Position()));

		//now pair up the freed up register with the new user
		r.first = new Descriptor(i, p->Last_Usage, t->Get_Name(), t->Get_Parent());

		return;

	}
	cout << "allocation needed!" << endl;
	throw::runtime_error("INTERNAL ERROR!");
}

void Selector::Pair_Up(Token* r, Descriptor* t)
{
	for (auto& i : Registers)
		if (i.second->Get_Name() == r->Get_Name() || i.second == r->ID) {
			i.first = t;
			return;
		}
}

void Selector::Break_Up(Token* r)
{
	for (auto& i : Registers)
		if (i.second->Get_Name() == r->Get_Name() || i.second == r->ID) {
			i.first = nullptr;
			return;
		}
}

int Selector::Get_Numerical_Parameter_Register_Count(vector<Node*> Parameters)
{
	if(sys->Info.OS == "win") {
		//first get the amount of all non decimal registers
		int Non_Decimal_Register_Count = 0;
		for (auto& i : Parameter_Registers) {
			if (!i[0]->is(TOKEN::DECIMAL))
				Non_Decimal_Register_Count++;
		}
		//then get the amount of all decimal registers
		int Decimal_Register_Count = 0;
		for (auto& i : Parameter_Registers) {
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
		for (auto& i : Parameter_Registers) {
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
		for (auto& i : Parameter_Registers) {
			if (!i[0]->is(TOKEN::DECIMAL))
				Non_Decimal_Register_Count++;
		}
		//then get the amount of all decimal registers
		int Decimal_Register_Count = 0;
		for (auto& i : Parameter_Registers) {
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
		for (auto& i : Parameter_Registers) {
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

vector<pair<Descriptor*, Token*>> Selector::Get_Register_Type(long f)
{
	vector<pair<Descriptor*, Token*>> Result;
	for (auto& i : Registers) {
		if (i.second->is(f))
			Result.push_back(i);
	}
	return Result;
}

Token* Selector::Get_Larger_Register(Token* Reg, Token* token)
{
	if (Reg->Get_Size() == token->Get_Size())
		return Reg;

	if (Reg->Holder)
		return Get_Larger_Register(Reg->Holder, token);

	return nullptr;
}

Token* Selector::Get_Smaller_Register(Token* Reg, Token* token)
{
	if (Reg->Get_Size() == token->Get_Size())
		return Reg;

	for (auto i : Reg->Childs) {
		if (Get_Smaller_Register(i, token))
			return Get_Smaller_Register(i, token);
	}

	return nullptr;
}

Token* Selector::Get_Largest_Register(Token* Reg)
{
	if (Reg->Holder)
		return Get_Largest_Register(Reg->Holder);

	return Reg;
}

void Selector::DeAllocate_Stack(int Amount, vector<IR*>* list, int i)
{
	//add rsp, 123 * 16
	//if used call in scope use stack.size() % 16 = 0;
	list->insert(list->begin() + i, new IR(new Token(TOKEN::OPERATOR, "+"), { new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK",  _SYSTEM_BIT_SIZE_), new Token(TOKEN::NUM | TOKEN::STACK_ALLOCATION_CONSTANT, to_string(Amount), _SYSTEM_BIT_SIZE_) }, nullptr));
}

void Selector::Allocate_Stack(int Amount, vector<IR*>* list, int i)
{
	//sub rsp, 123 * 16
	//if used call in scope use stack.size() % 16 = 0;
	list->insert(list->begin() + i, new IR(new Token(TOKEN::OPERATOR, "-"), { new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK", _SYSTEM_BIT_SIZE_), new Token(TOKEN::NUM | TOKEN::STACK_ALLOCATION_CONSTANT, to_string(Amount), _SYSTEM_BIT_SIZE_) }, nullptr));
}

void Selector::Init_Stack(Node* Func)
{
	for (auto i : Func->Defined){
		if (!i->Requires_Address /* && !sys->Info.Debug --> no need the memory needing variables are already need_address = true*/ )
			continue;
		long long Memory_Type = 0;
		if (i->Format == "decimal")
			Memory_Type = TOKEN::DECIMAL;

		Stack.push_back({ nullptr, new Token(TOKEN::MEMORY | Memory_Type | TOKEN::LOCAL_VARIABLE_SCOPE, { new Token(TOKEN::CONTENT, i->Name, i->Size, i->Scope)}, i->Size, i->Name, i->Scope)});
	}

	Stack.push_back({ nullptr, new Token(TOKEN::MEMORY | TOKEN::CALL_PARAMETER_SPACE, { new Token(TOKEN::CONTENT, ".CALL_PARAMETER_SPACE", Func->Size_of_Call_Space)}, Func->Size_of_Call_Space, ".CALL_PARAMETER_SPACE")});

	
}

Token* Selector::Get_Memory_Location(Token* v)
{
	for (auto& i : Stack) {
		if (i.second->Get_Name() == v->Get_Name()) {
			return new Token(*i.second);
		}
	}
	return nullptr;
}

void Selector::Clean_Stack()
{
	Stack.clear();
}

long long Selector::Calculate_Memory_Address(Token* m)
{
	long long Result = 0;

	for (auto i : { TOKEN::CALL_PARAMETER_SPACE, TOKEN::REGISTER_SAVE_SPACE, TOKEN::LOCAL_VARIABLE_SCOPE, TOKEN::PUSH_SPACE,  TOKEN::PARAMETER_SPACE})
		for (auto& j : Stack) {
			//this may need flag checkings
			if (j.second->Get_Name() == m->Get_Name() && m->is(i))
				return Result;
			if (j.second->is(i)) {
				Result += j.second->Get_Size();
			}
		}

	Report(Observation(ERROR, "INTERNAL ERROR WHILE TRYING TO FIND FROM STACK!!!", Position()));
}

long long Selector::Calculate_Memory_Address(long long F)
{
	long long Result = 0;

	for (auto i : { TOKEN::CALL_PARAMETER_SPACE, TOKEN::REGISTER_SAVE_SPACE, TOKEN::LOCAL_VARIABLE_SCOPE, TOKEN::PUSH_SPACE,  TOKEN::PARAMETER_SPACE }) {
		if ((F & i) == i)
			return Result;
		for (auto& j : Stack) {
			if (j.second->is(i)) {
				Result += j.second->Get_Size();
			}
		}
	}

	Report(Observation(ERROR, "INTERNAL ERROR WHILE TRYING TO FIND FROM STACK!!!", Position()));

}

IR* Selector::Get_Opcode(IR* i)
{
	vector<int> sizes;
	//this gives the selector information about the sizes of these arguments
	for (auto s : i->Arguments)
		sizes.push_back(s->Get_Size());

	for (auto opc : Opcodes) {
		if (opc->Intermediate_Alias != i->OPCODE->Get_Name())
			continue;
		for (auto& o : opc->Order) {
			//check if this order has same amount of arguments as i.
			if (o.Order.size() != sizes.size())
				continue;	//this is wrong order
			for (int j = 0; j < sizes.size(); j++) {
				if (!(o.Order[j].Min_Size <= sizes[j] && o.Order[j].Max_Size >= sizes[j]))
					goto Wrong;
			}
			//if (!Check_Resource_Availability(i, o))
			//	goto Wrong;
			for (int j = 0; j < sizes.size(); j++) {
				if (!o.Order[j].Type->is(i->Arguments[j]->Get_Flags()))
					goto Wrong;
			}
			return opc;
		Wrong:;
		}

		//We want to skip nullptr orders, they are there because we need the opcode asm hex number, but dont want to count order as a nessessity for selection.
		bool Skip_NULLPTR_ORDER = false;
		if (opc->Order.size() > 1 && opc->Order[0].Order[0].Type == nullptr)
			Skip_NULLPTR_ORDER = true;

		if (opc->Order.size() - Skip_NULLPTR_ORDER < 1) {
			if (sizes.size() == 0)
				return opc;
		}
	}
	string args = "(";
	for (auto j : i->Arguments)
		args += j->Get_Name() + "[" + to_string(j->Get_Size()) + "]" + ", ";
	args += ")";
	Report(Observation(ERROR, "No suitable OPCODE found for " + i->OPCODE->Get_Name() + args));
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

pair<long long, long long> Selector::Compute_Function_Territory(vector<IR*> Irs, long long i)
{
	pair<long long, long long> Result;
	for (long long Current_Location = i; Current_Location > 0; Current_Location--)
		if (Irs[Current_Location]->is(TOKEN::START_OF_FUNCTION)) {
			Result.first = Current_Location;
			break;
		}

	for (long long Current_Location = i; Current_Location < Irs.size(); Current_Location++)
		if (Irs[Current_Location]->is(TOKEN::END_OF_FUNCTION)) {
			Result.second = Current_Location;
			break;
		}

	return Result;
}

vector<Token*> Selector::Get_Stack_Deallocators_And_Allocators(pair<long long, long long> Function_Territory, vector<IR*> Irs)
{
	vector<Token*> Result;

	for (int i = Function_Territory.first; i < Function_Territory.second; i++) {
		for (auto j : Irs[i]->Arguments)
			for (auto k : j->Get_All(TOKEN::STACK_ALLOCATION_CONSTANT)) {
				Result.push_back(k);
			}
	}

	return Result;
}

pair<Descriptor*, Token*>* Selector::Get_Register_User(Token* R)
{
	for (auto &i : Registers) {
		if (i.second == R) {
			if (i.first)
				return &i;
			for (auto j : R->Childs) {
				if (Get_Register_User(j))
					return Get_Register_User(j);
			}
			return nullptr;
		}
	}
}

