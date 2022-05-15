#include "../../H/Assembler/Assembler.h"

#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Safe.h"
#include "../../H/Docker/Docker.h"
#include "../../H/Docker/Mangler.h"

Selector* selector;

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
vector<class IR*> Assembler::Parser_Post_Prosessor(vector<class IR*> IRs)
{
    for (auto& i : IRs) {

        vector<Token*> Arguments = i->Arguments;

        for (auto& j : selector->Opcodes) {

            if (i->OPCODE->Name != j->OPCODE->Name)
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

vector<Byte_Map*> Assembler::Intermediate_Encoder(vector<class IR*> IRs)
{
    vector<Byte_Map*> Result;

    for (auto& ir : IRs) {

        Result.push_back(selector->Build(ir));

    }

}

void Assembler::Factory(){

}
