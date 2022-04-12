#include "../../H/Assembler/Assembler.h"

vector<string> Assembler::Tokenizer(string Input){
    vector<Word*> Tokens;
    
    char Previus_Char = '\0';
    string Token = "";

    Input = Input.replace(Input.find("\t"), 1, " ");
    Input = Input.replace(Input.find("\r"), 1, " ");

    pair<char, char> Previus_Char_Group;

    for (auto c : Input){

        if (c >= CHAR_GROUPS::BIG_LETTER_GROUP_START_INDEX && c <= CHAR_GROUPS::BIG_LETTER_GROUP_END_INDEX){
            //Because letters basically dont stick to anything but letters and numbers
            //so we can just flush anything else away
            if (
                Previus_Char_Group.first != CHAR_GROUPS::BIG_LETTER_GROUP_START_INDEX &&
                Previus_Char_Group.first != CHAR_GROUPS::NUMBER_GROUP_START_INDEX
            ){
                Tokens.push_back(new Word(Token));
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
            }
            else{
                Token += c;
            }
        }
        else if (c >= CHAR_GROUPS::OPERATOR_GROUP_START_INDEX && c <= CHAR_GROUPS::OPERATOR_GROUP_END_INDEX){
            //sticks to no one.
            
        }
    
    }

    return Tokens;
}

void Assembler::Factory(){

}
