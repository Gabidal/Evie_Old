#include "../../H/Lexer/Definer.h"

//a : b = c + find(a) * (a + b)

	enum Type
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


int getWord(string source, int continu)
{
    int LayerCount = 0;
    int i = continu;
    do 
    {
        if (source[i] == '(')
        {
            LayerCount++;
        }
        if (source[i] == ')')
        {
            LayerCount--;
        }
        i++;
        
    }while(LayerCount > 0);
    return i;
}

	bool IsOperator(char c)
	{
		return (c >= 33 && c <= 47 && c != COMMENT && c != STRING) || (c >= 58 && c <= 63) || c == 94 || c == 124 || c == 126;
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
			return TEXT;
		}
		else if (IsDigit(c))
		{
			return NUMBER;
		}
		else if (IsContent(c))
		{
			return CONTENT;
		}
		else if (IsOperator(c))
		{
			return OPERATOR;
		}
		else if (IsComment(c))
		{
			return COMMENT;
		}
		else if (IsString(c))
		{
			return STRING;
		}
		else if (c == '\n')
		{
			return END;
		}

		return UNSPECIFIED;
	}

    int translateIdentity(Type t, string text, Word *&w)
    {
        if (t == TEXT)
        {
            if (text == "while" || text == "type" || text == "func" || text == "var" || text == "new" || text == "using" || text == "static" || text == "return" || text == "if" || text == "else")
            {
                return _KEYWORD;
            }
            else
            {
                return _TEXT;
            }
        }
        else if (t == COMMENT)
        {
            return _COMMENT;
        }
        else if (t == NUMBER)
        {
            return _NUMBER;
        }
        else if (t == CONTENT)
        {
            Definer d;
            d.Direct(text.substr(1, text.size() - 2));
            w->Tokens = d.output;
            return _PAREHTHESIS;
        }
        else if (t == OPERATOR)
        {
            return _OPERATOR;
        }
        else if (t == STRING)
        {
            return _STRING;
        }
        else if (t == END)
        {
            return _END;
        }
        return 0;
    }

void Definer::Define()
{
    Type Base = UNSPECIFIED;
	Type Current = UNSPECIFIED;
    int start = 0;
	int i = 0;
    for (; i < int(Lines.size()); i++)
    {
        Current = GetType(Lines.at(i));
        if (Base == UNSPECIFIED)
        {
            Base = Current;
			start = i;
        }

        if (Base == CONTENT && Current == CONTENT)
        {
            i = getWord(Lines, i);
            Word *w = new Word("");
            w->WORD = Lines.substr(start, i-start);
            w->Flags = translateIdentity(Base, w->WORD, w);
            output.push_back(w);
            Base = UNSPECIFIED;
            i--;
        }
        
        if (Base != Current && Base != UNSPECIFIED)
        {
            Word *w = new Word("");
            w->WORD = Lines.substr(start, i-start);
            w->Flags = translateIdentity(Base, w->WORD, w);
            output.push_back(w);
            Base = UNSPECIFIED;
            i--;
        }
    }

	Word *w = new Word("");
    w->WORD = Lines.substr(start, i-start);
    w->Flags = translateIdentity(Base, w->WORD, w);
    output.push_back(w);
}

void Definer::OpenFile(const char* fileName)
{
    ifstream file(fileName);
    string BUFFER;
    if (file.is_open() != true)
    {
        cout << "File not found!\n";
        exit(1);
    }
    else
    {
        string Line;
        while (getline(file, Line))
        {
            BUFFER += Line + "\n";
        }
    }
    Lines = BUFFER;
        Define();
}

void Definer::Direct(string raw)
{
    Lines = raw;
    Define();
}