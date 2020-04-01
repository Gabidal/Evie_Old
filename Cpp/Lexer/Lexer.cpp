#include "../../H/Lexer/Lexer.h"

//a : b = c + find(a) * (a + b)
#define __COMMENT '#'
#define __STRING '\"'

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
    int i = source.find(__STRING, continu + 1);

    if (i == -1)
    {
        cout << "Error:: Can't find end of string" << endl;
    }

    int length = i - continu;
    return i + 1;
}

	bool IsOperator(char c)
	{
		return (c >= 33 && c <= 47 && c != __COMMENT && c != __STRING) || (c >= 58 && c <= 64) || c == 94 || c == 124 || c == 126;
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
        if (text == "while" || text == "type" || text == "func" ||text == "use"|| text == "if" )//|| text == "export")
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
        Lexer d;
        d.Direct(text.substr(1, text.size() - 2));
        w->Tokens = d.output; 
        return _PAREHTHESIS;
    }
    else if (t == STRING)
    {
        Lexer d;
        d.Direct(text.substr(1, text.size() - 2));
        w->Tokens = d.output;
        return _STRING;
    }
    else if (t == OPERATOR)
    {
        return _OPERATOR;
    }
    else if (t == END)
    {
        return _END;
    }
    return 0;
}

bool IsPartOf(Type previous, Type current, char c)
{
    if (current == previous || previous == UNSPECIFIED)
    {
        return true;
    }

    switch (previous)
    {
        case TEXT:
        {
            return current == NUMBER;
        }

        case NUMBER:
        {
            return c == '.';
        }

        default: return false;
    }
}

void Lexer::Define()
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
            i = getWord(Lines, i, '(', ')');
            Word* w = new Word("");
            w->WORD = Lines.substr(start, i - start);
            w->Flags = translateIdentity(Base, w->WORD, w);
            output.push_back(w);
            Base = UNSPECIFIED;
            i--;
        }
        else if (Base == STRING && Current == STRING)
        {
            i = getString(Lines, i);
            Word* w = new Word("");
            w->WORD = Lines.substr(start, i - start);
            w->Flags = translateIdentity(Base, w->WORD, w);
            output.push_back(w);
            Base = UNSPECIFIED;
            i--;
        }
        
        if (!IsPartOf(Base, Current, Lines.at(i)) && Base != UNSPECIFIED)
        {
            Word *w = new Word("");
            w->WORD = Lines.substr(start, i-start);
            w->Flags = translateIdentity(Base, w->WORD, w);
            output.push_back(w);
            Base = UNSPECIFIED;
            i--;
        }
    }
    if (Base != UNSPECIFIED)
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

void Lexer::OpenFile(const char* fileName)
{
    ifstream file(fileName);
    if (file.is_open() != true)
    {
		cout << "File not found: " << fileName << '\n';
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
