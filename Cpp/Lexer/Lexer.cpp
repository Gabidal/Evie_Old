#include "../../H/Lexer/Lexer.h"

//a : b = c + find(a) * (a + b)
#define ___COMMENT__ '#'
#define ___STRING__ '\"'

	enum class Type
	{
		UNSPECIFIED,
		TEXT,
		COMMENT,
		NUMBER,
		CONTENT,
		OPERATOR,
		STRING,
		END
	};


int getWord(string source, int continu, char StartType, char EndType)
{
    int LayerCount = 0;
    int i = continu;
    do 
    {
        if (source[i] == StartType)
        {
            LayerCount++;
        }
        if (source[i] == EndType)
        {
            LayerCount--;
        }
        i++;
        
    }while(LayerCount > 0);
    return i;
}

int getString(string source, int continu)
{
    int i = source.find(___STRING__, continu + 1);

    if (i == -1)
    {
        cout << "Error: Can't find end of string" << endl;
    }

    int length = i - continu;
    return i + 1;
}

	bool IsOperator(char c)
	{
		return (c >= 33 && c <= 47 && c != ___COMMENT__ && c != ___STRING__) || (c >= 58 && c <= 64) || c == 94 || c == 124 || c == 126 ;
	}

	bool IsDigit(char c)
	{
		return c >= 48 && c <= 57;
	}

	bool IsText(char c)
	{
		return (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95;
	}

	bool IsContent(char c)
	{
		return c == '(';
	}

	bool IsComment(char c)
	{
		return c == '#';
	}

	bool IsString(char c)
	{
		return c == '\"';
	}

	Type GetType(char c)
	{
		if (IsText(c))
		{
			return Type::TEXT;
		}
		else if (IsDigit(c))
		{
			return Type::NUMBER;
		}
		else if (IsContent(c))
		{
			return Type::CONTENT;
		}
		else if (IsOperator(c))
		{
			return Type::OPERATOR;
		}
		else if (IsComment(c))
		{
			return Type::COMMENT;
		}
		else if (IsString(c))
		{
			return Type::STRING;
		}
		else if (c == '\n')
		{
			return Type::END;
		}

		return Type::UNSPECIFIED;
	}

int translateIdentity(Type t, string text, Word *&w)
{
    if (t == Type::TEXT)
    {
        if (text == "while" || text == "type" || text == "func" ||text == "use"|| text == "if" )//|| text == "export")
        {
            return _KEYWORD;
        }
        else
        {
            return _TEXT;
        }
    }
    else if (t == Type::COMMENT)
    {
        return _COMMENT;
    }
    else if (t == Type::NUMBER)
    {
        return _NUMBER;
    }
    else if (t == Type::CONTENT)
    {
        Lexer d;
        d.Direct(text.substr(1, text.size() - 2));
        w->Tokens = d.output; 
        return _PAREHTHESIS;
    }
    else if (t == Type::STRING)
    {
        Lexer d;
        d.Direct(text.substr(1, text.size() - 2));
        w->Tokens = d.output;
        return _STRING;
    }
    else if (t == Type::OPERATOR)
    {
        return _OPERATOR;
    }
    else if (t == Type::END)
    {
        return _END;
    }
    return 0;
}

bool IsPartOf(Type previous, Type current, char c)
{
    if (current == previous || previous == Type::UNSPECIFIED)
    {
        return true;
    }

    switch (previous)
    {
        case Type::TEXT:
        {
            return current == Type::NUMBER || (c == '@');
        }

        case Type::NUMBER:
        {
            return c == '.';
        }

        default: return false;
    }
}

void Lexer::Define()
{
    Type Base = Type::UNSPECIFIED;
	Type Current = Type::UNSPECIFIED;
    int start = 0;
	int i = 0;
    for (; i < int(Lines.size()); i++)
    {
        Current = GetType(Lines.at(i));
        if (Base == Type::UNSPECIFIED)
        {
            Base = Current;
			start = i;
        }

        if (Base == Type::CONTENT && Current == Type::CONTENT)
        {
            i = getWord(Lines, i, '(', ')');
            Word* w = new Word("");
            w->WORD = Lines.substr(start, i - start);
            w->Flags = translateIdentity(Base, w->WORD, w);
            output.push_back(w);
            Base = Type::UNSPECIFIED;
            i--;
        }
        else if (Base == Type::STRING && Current == Type::STRING)
        {
            i = getString(Lines, i);
            Word* w = new Word("");
            w->WORD = Lines.substr(start, i - start);
            w->Flags = translateIdentity(Base, w->WORD, w);
            output.push_back(w);
            Base = Type::UNSPECIFIED;
            i--;
        }
        
        if (!IsPartOf(Base, Current, Lines.at(i)) && Base != Type::UNSPECIFIED)
        {
            Word *w = new Word("");
            w->WORD = Lines.substr(start, i-start);
            w->Flags = translateIdentity(Base, w->WORD, w);
            output.push_back(w);
            Base = Type::UNSPECIFIED;
            i--;
        }
    }
    if (Base != Type::UNSPECIFIED)
    {
        Word* w = new Word("");
        w->WORD = Lines.substr(start, i - start);
        w->Flags = translateIdentity(Base, w->WORD, w);
        output.push_back(w);
    }
}

string ReplaceString(string subject, const string& search, const string& replace)
{
	int pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

string Working_Dir = "";

void Lexer::OpenFile(const char* FileName)
{
    string Name = Update_Dir(FileName);
    ifstream file(Working_Dir + Name);
    if (file.is_open() != true)
    {
		cout << "Error: File not found: " << Working_Dir + Name << '\n';
        exit(1);
    }
    else
    {
        string Line;
        while (getline(file, Line))
        {
			if ((Line.size() > 0) && (Line.at(0) == '#'))
			{
				continue;
			}
            Remove_Comment(Line);
            Lines += Line + " ";
            //Lines = Line; 
            //Lines = ReplaceString(Lines, "\t", " "); 
            //Lines = ReplaceString(Lines, "\n", "");
            //Define();
            //LineNumber++;
        }
    }
	Lines = ReplaceString(Lines, "\t", " ");
    Define();
}

void Lexer::Direct(string raw)
{
    Lines = raw;
    Define();
}

void Lexer::Remove_Comment(string& line)
{
    int start = line.find("#");

    if (start == -1)
    {
        return;
        //throw std::runtime_error("Error: Couldn't find the start of a comment");
    }

    int length = line.size() - start;

    line = line.erase(start, length);
}

string Lexer::Update_Dir(string File_Name)
{
    int i = File_Name.find_last_of('/');
    if (i != -1)
    {
        Working_Dir += File_Name.substr(0, i + 1);
        return File_Name.substr(i + 1);
    }
    return File_Name;
}
