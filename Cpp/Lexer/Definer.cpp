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
        else if (source[i] == ')')
        {
            LayerCount--;
        }
        i++;
    }while(LayerCount > 0);
    return i;
}

	bool IsOperator(char c)
	{
		return c >= 33 && c <= 47 && c != COMMENT && c != STRING || c >= 58 && c <= 63 || c == 94 || c == 124 || c == 126;
	}

	bool IsDigit(char c)
	{
		return c >= 48 && c <= 57;
	}

	bool IsText(char c)
	{
		return c >= 65 && c <= 90 || c >= 97 && c <= 122 || c == 95;
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

    int translateIdentity(Type t, string text, Word &w)
    {
        if (t == TEXT)
        {
            if (text == "while" || text == "type" || text == "func" || text == "var" || text == "new" || text == "use" || text == "static")
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
            Definer d(text.substr(1, text.size() - 1));
            w.Tokens = d.output;
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
    int start = 0;
    for (int i = 0; i < Lines.size(); i++)
    {
        Type Current = GetType(Lines.at(i));
        if (Current == CONTENT)
        {
            i = getWord(Lines, i);
            Word word("");
            word.WORD = Lines.substr(start, i-start+1);
            word.Flags |= translateIdentity(Base, word.WORD, word);
            output.push_back(word);
            Base = Current;
            start = i;
            continue;
        }
        if (Current != Base)
        {
            Word word("");
            word.WORD = Lines.substr(start, i-start);
            word.Flags |= translateIdentity(Base, word.WORD, word);
            output.push_back(word);
            Base = Current;
            start = i;
        }
    }
}