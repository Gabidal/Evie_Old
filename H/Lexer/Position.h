#ifndef _POSITION_H_
#define _POSITION_H_


class Position
{
private:
    int Line = 0;
    int Character = 0;
    int Local = 0;
    int Absolute = 0;
    const char* File_Name = "";
public:

    Position(int line = 0, int character = 0, int local = 0, int absolute = 0);

    int GetLine() const
    {
        return Line;
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
};

#endif