#include "../../H/Assembler/Assembler.h"

#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Safe.h"
#include "../../H/Docker/Docker.h"
#include "../../H/Docker/Mangler.h"

#include "../../H/Assembler/Assembler_Types.h"

#include "../../H/Nodes/IR.h"

extern Selector* selector;

Assembler::Assembler(string Input){
	ifstream file(Input, std::ios::binary);

	if (!file.is_open()) {
		throw::runtime_error("FILE NOT FOUND!");
	}
	file.seekg(0, ios_base::end);
	long long size = file.tellg();
	char* Buffer = new char[size + 1];
	file.seekg(0, ios_base::beg);
	file.read(Buffer, size);
	Buffer[size] = '\0';
	file.close();

    vector<Word*> Words = Tokenizer(string(Buffer));

    vector<Token*> Tokens = Grouper(Words);

    vector<IR*> IRs = Parser(Tokens);

    IRs = Parser_Post_Prosessor(IRs);

    Output = Intermediate_Encoder(IRs);
}

Assembler::Assembler(vector<IR*> IRs){

    for (int i = 0; i < IRs.size(); i++){
        if (IRs[i]->OPCODE->Has({TOKEN::END_OF_FUNCTION, TOKEN::END_OF_LOOP})){
            IRs.erase(IRs.begin() + i--);
        }
    }

    vector<IR*> tmp = Parser_Post_Prosessor(IRs);
    Output = Intermediate_Encoder(tmp);
}

vector<Word*> Assembler::Tokenizer(string Input){
    vector<Word*> Tokens;
    
    char Previus_Char = '\0';
    string Token = "";
    int Current_Flag = 0;

    Input = Input.replace(Input.find("\t"), 1, " ");
    Input = Input.replace(Input.find("\r"), 1, " ");

    pair<char, char> Previus_Char_Group;

    for (int i = 0; i < Input.size(); i++){

        char c = Input[i];

        if (c >= CHAR_GROUPS::BIG_LETTER_GROUP_START_INDEX && c <= CHAR_GROUPS::BIG_LETTER_GROUP_END_INDEX){
            //Because letters basically dont stick to anything but letters and numbers
            //so we can just flush anything else away
            if (
                Previus_Char_Group.first != CHAR_GROUPS::BIG_LETTER_GROUP_START_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::NUMBER_GROUP_START_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::HASH_TAG_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::DOLLAR_SIGN_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::PERCENT_SIGN_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::AT_SIGN_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::UNDERLINE_INDEX
            ){
                Tokens.push_back(new Word(Token, Current_Flag));
                Token = "";
            }
            else{
                Token += c;
                Current_Flag = WORD_FLAGS::LABEL | WORD_FLAGS::OPCODE | WORD_FLAGS::REGISTER | WORD_FLAGS::TEXT;
            }
        }
        else if (c >= CHAR_GROUPS::NUMBER_GROUP_START_INDEX && c <= CHAR_GROUPS::NUMBER_GROUP_END_INDEX){
            //Numbers dont stick to anything other than letters
            if (
                Previus_Char_Group.first != CHAR_GROUPS::BIG_LETTER_GROUP_START_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::NUMBER_GROUP_START_INDEX
            ){
                Tokens.push_back(new Word(Token, Current_Flag));
                Token = "";
            }
            else{
                Token += c;
                Current_Flag = WORD_FLAGS::NUMBER;
            }
        }
        else if (c >= CHAR_GROUPS::OPERATOR_GROUP_START_INDEX && c <= CHAR_GROUPS::OPERATOR_GROUP_END_INDEX){
            //sticks to no one.
            Tokens.push_back(new Word(Token, Current_Flag));
            Token = c;
            Current_Flag = WORD_FLAGS::OPERATOR;
        }
        else if (c == CHAR_GROUPS::OPENING_PARANTHESIS_INDEX || c == CHAR_GROUPS::OPENING_BRACKET_INDEX){
            Tokens.push_back(new Word(Token, Current_Flag));

            //first get the contents lenght
            int Contents_Length = Get_Paranthesis_Content_Length(c, i, Input);

            //Now extract this content with substr
            string Content = Input.substr(i + 1, Contents_Length - 1);

            //now parse this content
            vector<Word*> Content_Tokens = Tokenizer(Content);

            //now add the content tokens to the tokens
            //dont need to affect current flag
            Word* Content_Word = new Word(to_string(c), WORD_FLAGS::MEMORY);
            Content_Word->Childs = Content_Tokens;

            Tokens.push_back(Content_Word);

            i += Contents_Length;
        }
        else if (c == CHAR_GROUPS::HASH_TAG_INDEX || c == CHAR_GROUPS::DOLLAR_SIGN_INDEX || c == CHAR_GROUPS::PERCENT_SIGN_INDEX || c == CHAR_GROUPS::AT_SIGN_INDEX || c == CHAR_GROUPS::UNDERLINE_INDEX || c == CHAR_GROUPS::QUESTION_MARK_INDEX){
            //Because letters basically dont stick to anything but letters and numbers
            //so we can just flush anything else away
            if (
                Previus_Char_Group.first != CHAR_GROUPS::BIG_LETTER_GROUP_START_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::NUMBER_GROUP_START_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::HASH_TAG_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::DOLLAR_SIGN_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::PERCENT_SIGN_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::AT_SIGN_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::UNDERLINE_INDEX
            ){
                Tokens.push_back(new Word(Token, Current_Flag));
                Token = "";
            }
            else{
                Token += c; 
                Current_Flag = WORD_FLAGS::LABEL | WORD_FLAGS::OPCODE | WORD_FLAGS::REGISTER | WORD_FLAGS::TEXT;
            }
        }
        else if (c == CHAR_GROUPS::LABEL_START_CHARACHTER_INDEX) {
            Tokens.push_back(new Word(Token, Current_Flag));
            Token = "";

            Token = CHAR_GROUPS::LABEL_START_CHARACHTER_INDEX;
            Current_Flag = WORD_FLAGS::LABEL_INDICATOR;
        }
        else if (c == CHAR_GROUPS::LINE_ENDING_INDEX) {
            Tokens.push_back(new Word(Token, Current_Flag));

            Token = CHAR_GROUPS::LINE_ENDING_INDEX;
            Current_Flag |= WORD_FLAGS::LINE_ENDING;
        }
        else{
            //Sticks to no one.
            Tokens.push_back(new Word(Token, Current_Flag));

            if (c != CHAR_GROUPS::SPACE_INDEX){
                Tokens.push_back(new Word(to_string(c), WORD_FLAGS::UNKNOWN));
            }
        }
    }

    //get more accurate representation for the tokens
    for (int i = 0; i < Tokens.size(); i++) {
        if (Tokens[i]->is(WORD_FLAGS::TEXT)) {
            //check if the Token is a OPCODE
            Tokens[i]->Flags = 0;

            if (Tokens[i]->Flags == 0) {
                if (i + 1 < Tokens.size() && Tokens[i + 1]->is(WORD_FLAGS::LABEL_INDICATOR)) {
                    Tokens[i]->Flags = WORD_FLAGS::LABEL;
                    Tokens.erase(Tokens.begin() + i + 1);
                    i--;
                }
            }

            //If the flags is still zero, it means that the token wasnt a label, try opcode
            if (Tokens[i]->Flags == 0) {
                for (auto& OPCODE : selector->Opcodes) {
                    if (OPCODE->OPCODE->Name == Tokens[i]->Name) {
                        Tokens[i]->Flags = WORD_FLAGS::OPCODE;
                        break;
                    }
                }
            }

            //If the flags is still zero, it means that the token wasnt a opcode, try register
            if (Tokens[i]->Flags == 0) {
                for (auto& REGISTER : selector->Registers) {
                    if (REGISTER.second->Name == Tokens[i]->Name) {
                        Tokens[i]->Flags = WORD_FLAGS::REGISTER;
                    }
                }
            }
        
            if (Tokens[i]->Flags == 0) {
                Alias* Alias_Reference = Tokens[i]->is(ALIASES);

                if (Alias_Reference != nullptr) {
                    Tokens[i]->Name = Alias_Reference->Name;

                    //look if the selector has a size identifier that is same as one of the aliases
                    for (auto& size : selector->Size_Identifiers) {
                        if (Alias_Reference->Has(size->Name)) {
                            Tokens[i]->Flags = WORD_FLAGS::SIZE_IDENTIFIER;
                            Tokens[i]->SIZE_IDENTIFIER_VALUE = size->Size;
                        }
                    }

                    if (Tokens[i]->Flags == 0) {
                        Tokens[i]->Flags = WORD_FLAGS::ALIAS;
                    }

                }
            }
        }
    }

    return Tokens;
}

int Assembler::Get_Paranthesis_Content_Length(char Opening_Character_Type, int Start_Index, string Input){
    int Open_Character_Count = 1;

    int Index = Start_Index;

    int Closing_Character = Get_Closing_Character(Opening_Character_Type);

    while (
        Open_Character_Count != 0 &&
        Index < Input.size()
    ){
        Open_Character_Count += (Input[Index] == Opening_Character_Type) - (Input[Index] == Closing_Character);

        Index++;
    }

    return Index - Start_Index;
}

char Assembler::Get_Closing_Character(char Opening_Character){
    if (Opening_Character == CHAR_GROUPS::OPENING_PARANTHESIS_INDEX)
        return CHAR_GROUPS::CLOSING_PARANTHESIS_INDEX;
    else if (Opening_Character == CHAR_GROUPS::OPENING_BRACKET_INDEX)
        return CHAR_GROUPS::CLOSING_BRACKET_INDEX;
    else
        return -1;
}

vector<Token*> Assembler::Grouper(vector<Word*> Tokens)
{
    vector<Token*> Result;
    //NOTE:
    //The DWORD and alike are stored by finding their sizes from the selector and then putting into the argument.
    for (int i = 0; i < Tokens.size(); i++) {
        Token* Current_Token = nullptr;

        if (Tokens[i]->is(WORD_FLAGS::OPCODE)) {
            int j = 0;
            //we need to slice the arguments for this opcode because the recursive feature for 
            //'<dword> <[rax]>' -> '<[rax]{size: 4}>', cases
            vector<Word*> Args;
            for (; j < Tokens.size() && !Tokens[j]->is(WORD_FLAGS::LINE_ENDING); j++) {
                Args.push_back(Tokens[j]);
            }

            //The commas are removed automatically.
            vector<Token*>  Disected_Args = Grouper(Args);

            Token* Opcode;
            for (auto& opc : selector->Opcodes) {
                if (opc->OPCODE->Name == Tokens[i]->Name) {
                    Opcode = new Token(*opc->OPCODE);
                    break;
                }
            }

            Opcode->Flags |= TOKEN::OPCODE;

            //we cant use the Current_Token because the order of the tokens would be incorrect,
            //because of how the opcode would have been added later than the args
            Result.push_back(Opcode);
            DOCKER::Append(Result, Disected_Args);

            Result.push_back(new Token(TOKEN::NEWLINE, "\n"));
        }
        else if (Tokens[i]->is(WORD_FLAGS::SIZE_IDENTIFIER)) {
            
            if (i + 1 > Tokens.size()) {
                Report(Observation(ERROR, "Missing content after size identifier", ASSEMBLER_SYNTAX_ERROR));
            }

            Token* Arg = Grouper({Tokens[i + 1]})[0];

            Arg->Size = Tokens[i]->SIZE_IDENTIFIER_VALUE;
            Current_Token = Arg;


            Tokens.erase(Tokens.begin() + i, Tokens.begin() + i + 1);
            i --;
        }
        else if (Tokens[i]->is(WORD_FLAGS::REGISTER)) {
            for (auto& r : selector->Registers)
                if (r.second->Name == Tokens[i]->Name)
                    Current_Token = new Token(*r.second);
        }
        else if (Tokens[i]->is(WORD_FLAGS::MEMORY)) {
            Token* Wrapper = new Token(TOKEN::MEMORY);

            Token* Content = Grouper({ Tokens[i]->Childs })[0];
            Content->Flags |= TOKEN::CONTENT;

            Wrapper->Childs.push_back(Content);

            Current_Token = Wrapper;
        }
        else if (Tokens[i]->is(WORD_FLAGS::NUMBER)) {
            Token* Number = new Token(TOKEN::NUM);
            Number->Name = Tokens[i]->Name;
        }
        else if (Tokens[i]->is(WORD_FLAGS::OPERATOR) && !Tokens[i]->is(vector<string>{",", "."})) {
            
            //The left side is probably already inside the Result list.
            Token* Left = Result.back();
            Token* Right = Grouper({ Tokens[i + 1] })[0];

            Token* Operator = new Token(TOKEN::OPERATOR, { Left, Right }, 0, Tokens[i]->Name);

            //remove the left side 
            Result.pop_back();

            //remove the right side and the operator
            Tokens.erase(Tokens.begin() + i, Tokens.begin() + i + 1);
            i--;

            Current_Token = Operator;
        }
        else if (Tokens[i]->is(WORD_FLAGS::LABEL_INDICATOR)) {
            if (i - 1 < 0)
                Report(Observation(ERROR, "Missing label name", ASSEMBLER_SYNTAX_ERROR));

            Current_Token = new Token(TOKEN::LABEL, Tokens[i - 1]->Name);
        }

        Result.push_back(Current_Token);
    }

    return Result;
}

vector<IR*> Assembler::Parser(vector<Token*> Tokens){
    vector<IR*> Result;

    for (int i = 0; i < Tokens.size(); i++) {

        if (Tokens[i]->is(TOKEN::OPCODE)) {

            vector<Token*> Args;

            for (int j = i + 1; j < Tokens.size() && !Tokens[j]->is(TOKEN::NEWLINE); Args.push_back(Tokens[j++]));

            Result.push_back(new IR(Tokens[i], Args, new Position()));
        }
        else if (Tokens[i]->is(TOKEN::LABEL)) {
            //This shouldt contain paranthesis nor return type, and it does, so find a way to remove everything other than the name itself.
            Tokens[i]->OG = MANGLER::Un_Mangle(Tokens[i]->Name);

            Result.push_back(new IR(Tokens[i], {}, new Position()));
        }
    }

    return Result;
}

//This function tries to find the mathing opcodes that are in the architecture files.
vector<IR*> Assembler::Parser_Post_Prosessor(vector<IR*> IRs)
{
    for (auto& i : IRs) {

        vector<Token*> Arguments = i->Arguments;

        for (auto& j : selector->Opcodes) {

            if (i->OPCODE->Name != j->Intermediate_Alias)
                continue;

            for (auto& Opcode_Variant : j->Order) {

                if (Opcode_Variant.Order.size() != Arguments.size())
                    continue;

                bool This_Opcode_Variant_Is_Suitable = true;

                int Arg_Index = 0;
                for (auto& Args : Opcode_Variant.Order) {

                    if (Arguments[Arg_Index]->Size <= Args.Max_Size && Arguments[Arg_Index]->Size >= Args.Min_Size) {

                        if (!Args.Type->is(Arguments[Arg_Index]->Flags)) {
                            This_Opcode_Variant_Is_Suitable = false;
                        }

                    }
                    else {
                        This_Opcode_Variant_Is_Suitable = false;
                    }

                    Arg_Index++;
                }

                if (This_Opcode_Variant_Is_Suitable) {
                    i->Order.push_back(Opcode_Variant);

                    goto Found_Suitable_Opcode;
                }

            }
        }

    Found_Suitable_Opcode:;
    }

    return IRs;
}

vector<Byte_Map_Section*> Assembler::Intermediate_Encoder(vector<IR*> IRs)
{
    vector<Byte_Map_Section*> Result;

    for (int i = 0; i < IRs.size(); i++) {
        if (IRs[i]->OPCODE->Name == "extern"){

            Generate_Symbol_Table_For(IRs[i]->Arguments[0]->Name, 0, 0, IRs[i]->Arguments[0]->Parent->Find(IRs[i]->Arguments[0]->Name));
            continue;

        }
        else if (!IRs[i]->is(TOKEN::SECTION))
            continue;

        Byte_Map_Section* Section = new Byte_Map_Section(IRs[i]->Arguments[0]->Name);

        for (auto& a : ALIASES){
            if (a.Name == "data"){
                if (a.Has(Section->Name)){
                    Section->Is_Data_Section = true;
                    break;
                }
            }
        }
        
        //Set the address relative to the previous section
        if (Result.size() > 0){
            Section->Calculated_Address = Result.back()->Calculated_Address + Result.back()->Calculated_Size;
        }

        int j = i + 1;
        if (j <= IRs.size()){
            for (; j < IRs.size(); j++){
                if (IRs[j]->is(TOKEN::SECTION))
                    break;

                if (IRs[j]->is(TOKEN::SET_DATA)){
                    Section->Is_Data_Section = true;
                }

                if (IRs[j]->is(TOKEN::LABEL)){
                    //If the IRs[i] is a label we need to add it to the symbol table.
                    Generate_Symbol_Table_For(IRs[j]->OPCODE->Name, Section->Calculated_Address + Section->Calculated_Size, Result.size() + 1, IRs[j]->OPCODE->Parent->Find(IRs[j]->OPCODE->OG));
                }
                else{
                    Byte_Map* Current = selector->Build(IRs[j]);
                    Current->Size = selector->Get_Size(Current);
                    //The address is calculated by adding the current sectoin starting address and the current size.
                    Current->Address = Section->Calculated_Address + Section->Calculated_Size;
                    Section->Calculated_Size += Current->Size;

                    Section->Byte_Maps.push_back(Current);
                }
            }
        }

        Result.push_back(Section);

        //because the current j is the already the next section go one back.
        i = j - 1;
    }

    Apply_Self_Recursion(Result);

    return Result;

}

//This function uses the now address that are calculated to go back to the IR level and replace all the
//labels with the correct address.
//After this this function will use the modified IR to generate this Byte_Map again with the new information.
void Assembler::Apply_Self_Recursion(vector<Byte_Map_Section*>& Sections){

    for (auto& section : Sections){
        for (auto& byte_map : section->Byte_Maps){

            for (auto& T : byte_map->Ir->Arguments){

                Go_Through_Token_And_Replace_Local_Labels_With_Numbers(T, byte_map);
                Calculate_Constant_Expressions(T);

            }

            //Now apply the new modifications and build new byte map from it.
            *byte_map = *selector->Build(byte_map->Ir);
        }
    }

}

void Assembler::Go_Through_Token_And_Replace_Local_Labels_With_Numbers(Token* Current, Byte_Map* Back_Reference, unordered_set<Token*>& Trace){

    if (Trace.find(Current) != Trace.end())
        return;

    Trace.insert(Trace.end(), Current);

    if (Current->is(TOKEN::LABEL)){
        Symbol_Data symbol = Symbol_Table.find(Current->Name)->second;

        if (symbol.Section_ID == 0){
            //This is an external symbol witch address we dont know.
            Back_Reference->Has_External_Label = true;

            return;
        }

        Current->Flags = TOKEN::NUM;
        Current->Size = _SYSTEM_BIT_SIZE_;

        //Calculate the distance between this label reference and the definition declaration address.
        Current->Name = symbol.Address - Back_Reference->Address;

    }
    else{
        for (auto& Content : Current->Get_All()){

            Go_Through_Token_And_Replace_Local_Labels_With_Numbers(Content, Back_Reference, Trace);

        }

    }
}

void Assembler::Go_Through_Token_And_Replace_Local_Labels_With_Numbers(Token* Current, Byte_Map* Back_Reference){

    unordered_set<Token*> tmp;

    Go_Through_Token_And_Replace_Local_Labels_With_Numbers(Current, Back_Reference, tmp);

}

//2 - 1 => 1
void Assembler::Calculate_Constant_Expressions(Token* Current, unordered_set<Token*>& Trace){

    if (Trace.find(Current) != Trace.end())
        return;

    Trace.insert(Trace.end(), Current);

    for (auto& Content : Current->Get_All({TOKEN::OFFSETTER, TOKEN::SCALER})){

        Calculate_Constant_Expressions(Content, Trace);

    }

    if (!Current->is({TOKEN::OFFSETTER, TOKEN::SCALER}))
        return;

    if (Current->Left->is(TOKEN::NUM) && Current->Right->is(TOKEN::NUM)){
        if (Current->Name == "+"){
                long long New_Val = atoi(Current->Left->Name.c_str()) + atoi(Current->Right->Name.c_str());

                Current->Name = to_string(New_Val);
                Current->Flags = TOKEN::NUM;
                Current->Size = Current->Left->Size;

                Current->Left = nullptr;
                Current->Right = nullptr;
        }
        else if (Current->Name == "-"){
                long long New_Val = atoi(Current->Left->Name.c_str()) - atoi(Current->Right->Name.c_str());

                Current->Name = to_string(New_Val);
                Current->Flags = TOKEN::NUM;
                Current->Size = Current->Left->Size;

                Current->Left = nullptr;
                Current->Right = nullptr;
        }
        else if (Current->Name == "*"){
                long long New_Val = atoi(Current->Left->Name.c_str()) * atoi(Current->Right->Name.c_str());

                Current->Name = to_string(New_Val);
                Current->Flags = TOKEN::NUM;
                Current->Size = Current->Left->Size;

                Current->Left = nullptr;
                Current->Right = nullptr;
        }
        else if (Current->Name == "/"){
                long long New_Val = atoi(Current->Left->Name.c_str()) / atoi(Current->Right->Name.c_str());

                Current->Name = to_string(New_Val);
                Current->Flags = TOKEN::NUM;
                Current->Size = Current->Left->Size;

                Current->Left = nullptr;
                Current->Right = nullptr;
        }
        else if (Current->Name == "%"){
                long long New_Val = atoi(Current->Left->Name.c_str()) % atoi(Current->Right->Name.c_str());

                Current->Name = to_string(New_Val);
                Current->Flags = TOKEN::NUM;
                Current->Size = Current->Left->Size;

                Current->Left = nullptr;
                Current->Right = nullptr;
        }
    }

}

void Assembler::Calculate_Constant_Expressions(Token* Current){

    unordered_set<Token*> tmp;

    Calculate_Constant_Expressions(Current, tmp);

}

void Assembler::Generate_Symbol_Table_For(string Label, long long Address, int Section_ID, Node* Origin){
    Symbol_Table.insert({Label, {Address, Section_ID, Origin}});
}