#ifndef _POSITION_H_
#define _POSITION_H_

#include <string>

using namespace std;

class Position
{
public:
    int Line = 0;
    int Character = 0;
    int Local = 0;
    int Absolute = 0;
    const char* File_Name = "";

    Position(int line = 0, int character = 0, int local = 0, int absolute = 0);

    int GetLine() const
    {
        return Line;
    }

    const char* GetFilePath() const {
        return File_Name;
    }

    int GetCharacter() const
    {
        return Character;
    }

    int GetLocal() const {
        return Local;
    }

    int GetAbsolute() const
    {
        return Absolute;
    }

    int GetFriendlyLine() const
    {
        return Line + 1;
    }

    int GetFriendlyCharacter() const
    {
        return Character + 1;
    }

    int GetFriendlyAbsolute() const
    {
        return Absolute + 1;
    }

    Position& NextLine()
    {
        Line++;
		Character = 0;
        Local++;
		Absolute++;
		return *this;
    }

    Position& NextCharacter()
	{
		Character++;
		Absolute++;
        Local++;
		return *this;
	}

    Position Clone() const
	{
		return Position(Line, Character, Local, Absolute);
	}

    string ToString() const 
    {
        return (string(File_Name) + ":" + to_string(GetFriendlyLine()) + ":" + to_string(GetFriendlyCharacter()));
    }
};

#endif