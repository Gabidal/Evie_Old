#ifndef _POSITION_H_
#define _POSITION_H_

class Position
{
private:
    int Line = 0;
    int Character = 0;
    int Absolute = 0;

public:

    Position(int line = 0, int character = 0, int absolute = 0)
	{
		Line = line;
		Character = character;
		Absolute = absolute;
	}

    Position operator+(const Position& other)
    {
        return Position(this->Line + other.Line, this->Character + other.Character, this->Absolute + other.Absolute);
    }

    Position& operator+=(const Position& other)
    {
        this->Line += other.Line;
        this->Character += other.Character;
        this->Absolute += other.Absolute;
        return *this;
    }

    int GetLine() const
    {
        return Line;
    }

    int GetCharacter() const
    {
        return Character;
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
		Absolute++;
		return *this;
    }

    Position& NextCharacter()
	{
		Character++;
		Absolute++;
		return *this;
	}

    Position Clone() const
	{
		return Position(Line, Character, Absolute);
	}
};

#endif