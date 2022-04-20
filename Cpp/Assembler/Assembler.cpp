#include "../../H/Assembler/Assembler.h"

vector<Word*> Assembler::Tokenizer(string Input){
    vector<Word*> Tokens;
    
    char Previus_Char = '\0';
    string Token = "";

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
                Tokens.push_back(new Word(Token));
                Token = "";
            }
            else{
                Token += c;
            }
        }
        else if (c >= CHAR_GROUPS::NUMBER_GROUP_START_INDEX && c <= CHAR_GROUPS::NUMBER_GROUP_END_INDEX){
            //Numbers dont stick to anything other than letters
            if (
                Previus_Char_Group.first != CHAR_GROUPS::BIG_LETTER_GROUP_START_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::NUMBER_GROUP_START_INDEX
            ){
                Tokens.push_back(new Word(Token));
                Token = "";
            }
            else{
                Token += c;
            }
        }
        else if (c >= CHAR_GROUPS::OPERATOR_GROUP_START_INDEX && c <= CHAR_GROUPS::OPERATOR_GROUP_END_INDEX){
            //sticks to no one.
            Tokens.push_back(new Word(Token));
            Token = c;
        }
        else if (c == CHAR_GROUPS::OPENING_PARANTHESIS_INDEX || c == CHAR_GROUPS::OPENING_BRACKET_INDEX){

            //first get the contents lenght
            int Contents_Length = Get_Paranthesis_Content_Length(c, i, Input);

            //Now extract this content with substr
            string Content = Input.substr(i + 1, Contents_Length - 1);

            //now parse this content
            vector<Word*> Content_Tokens = Tokenizer(Content);

            //now add the content tokens to the tokens
            Word* Content_Word = new Word(to_string(c));
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
                Tokens.push_back(new Word(Token));
                Token = "";
            }
            else{
                Token += c;
            }
        }
        else{
            //Sticks to no one.
            Tokens.push_back(new Word(Token));

            if (c != CHAR_GROUPS::SPACE_INDEX){
                Tokens.push_back(new Word(to_string(c)));
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

vector<Opcode*> Assembler::Grouper(vector<Word*> Tokens){
    return vector<Opcode*>();
}

void Assembler::Factory(){

}
